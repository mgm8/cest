--
-- sensor.vhd
-- 
-- Copyright (C) 2020, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
-- 
-- This file is part of CEST library.
-- 
-- CEST library is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
-- 
-- CEST library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- GNU Lesser General Public License for more details.
-- 
-- You should have received a copy of the GNU Lesser General Public License
-- along with CEST library. If not, see <http://www.gnu.org/licenses/>.
-- 
--

--! 
--! \brief Sensor simulation block.
--! 
--! \details This block has the purpose of simulate a image sensor using a PPM image as input.
--! 
--! \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
--! 
--! \version 0.1.0
--! 
--! \date 13/12/2017
--! 

library ieee;
    use ieee.std_logic_1164.all;
    use ieee.numeric_std.all;

library std;
    use std.textio.all;

entity Sensor is
    generic(
        DATA_BITS   : natural := 8;                             --! Pixel size in bits (Sensor dependent).
        CHANNELS    : natural := 3                              --! Pixel channels.
        );
    port(
        clk     : in std_logic;                                 --! Clock source.
        rst     : in std_logic;                                 --! Reset pin.
        pixclk  : out std_logic;                                --! Pixel clock.
        hsync   : out std_logic;                                --! Horizontal sync. (High when the end o a line is reached).
        vsync   : out std_logic;                                --! Vertical sync. (High when the end of the image is reached).
        data    : out std_logic_vector(DATA_BITS-1 downto 0)    --! Data output.
        );
end Sensor;

architecture behavior of Sensor is
 
    type t_ppm_file is file of character;
    type t_byte_arr is array (natural range <>) of bit_vector(7 downto 0);
 
    constant IMAGE_WIDTH            : natural := 800;
    constant IMAGE_HEIGTH           : natural := 600;
    constant IMAGE_FILE             : string := "/tmp/img_buf.pgm";
    constant BLANK_REGION_CLKS      : natural := 15;
 
    signal read_arr_byte            : t_byte_arr(0 to 199);
    signal byte_counter             : natural := 0;
    signal img_width_ready          : std_logic := '0';
    signal img_heigth_ready         : std_logic := '0';
    signal header_ready             : std_logic := '0';
    signal header_line              : natural := 0;
    signal header_col               : natural := 0;
    signal netpbm_magic_number      : natural := 0;
    signal byte_dump                : std_logic := '0';
    signal line_counter             : natural := 0;             --! Image line counter (vsync).
    signal column_counter           : natural := 0;             --! Image column counter (hsync).

begin
 
    read_image : process
        type ppm_file_t is file of character;
        file ppm_file           : ppm_file_t;
        variable char_v         : character;
        subtype byte_t is natural range 0 to 255;
        variable byte_v         : byte_t;
 
    begin
 
        data <= std_logic_vector(to_unsigned(0, DATA_BITS));

        file_open(ppm_file, IMAGE_FILE);

        vsync <= '0';
        hsync <= '0';
 
        while not endfile(ppm_file) loop
            wait until rising_edge(clk);

            pixclk <= '1';

            read(ppm_file, char_v);
            byte_v := character'pos(char_v);

            if (header_ready = '0') then
                hsync <= '0';

                if (byte_dump = '1') then
                    if (byte_v = 10) then
                        byte_dump <= '0';
                    else
                        null;
                    end if;
                else
                    if ((header_col = 0) and (byte_v = 35)) then                    -- Ignores a line with comment.
                        byte_dump <= '1';
                    else
                        if (header_line = 0) then
                            if (header_col = 0) then
                                if (byte_v = 80) then                               -- 80 = 0x50 = 'P'
                                    header_col <= header_col + 1;
                                else
                                    assert false report "Unknown image format!" severity error; 
                                end if;
                            elsif (header_col = 1) then
                                if (byte_v = 49) then                               -- 49 = 0x31 = '1'
                                    netpbm_magic_number <= 1;
                                    header_col <= header_col + 1;
                                elsif (byte_v = 50) then                            -- 50 = 0x32 = '2'
                                    netpbm_magic_number <= 2;
                                    header_col <= header_col + 1;
                                elsif (byte_v = 51) then                            -- 51 = 0x33 = '3'
                                    netpbm_magic_number <= 3;
                                    header_col <= header_col + 1;
                                elsif (byte_v = 52) then                            -- 52 = 0x34 = '4'
                                    netpbm_magic_number <= 4;
                                    header_col <= header_col + 1;
                                elsif (byte_v = 53) then                            -- 53 = 0x35 = '5'
                                    netpbm_magic_number <= 5;
                                    header_col <= header_col + 1;
                                elsif (byte_v = 54) then                            -- 54 = 0x36 = '6'
                                    netpbm_magic_number <= 6;
                                    header_col <= header_col + 1;
                                else
                                    assert false report "Unknown image format!" severity error; 
                                end if;
                            else
                                if (byte_v = 10) then                               -- 10 = 0x0A = '\n'
                                    header_line <= header_line + 1;
                                else
                                    null;
                                end if;
                            end if;
                            if (byte_v = 10) then                                   -- 10 = 0x0A = '\n'
                                header_col <= 0;
                                header_line <= header_line + 1;
                            end if;
                        elsif (header_line = 1) then
                            if (byte_v = 32) then                                   -- 32 = 0x20 = ' '
                                header_col <= header_col + 1;
                            elsif (byte_v = 10) then
                                header_col <= 0;
                                header_line <= header_line + 1;
                            else
                                if (header_col = 0) then
                                    null;
                                elsif (header_col = 1) then
                                    null;
                                else
                                    header_col <= 0;
                                    header_line <= header_line + 1;
                                end if;
                            end if;
                        elsif (header_line = 2) then
                            if (byte_v = 10) then
                                header_ready <= '1';
                            else
                                header_col <= header_col + 1;
                            end if;
                        else
                            assert false report "Unexpected condition reached: Netpbm image header overflow!" severity warning;
                        end if;
                    end if;
                end if;

                wait until falling_edge(clk);

                pixclk <= '0';

            else
                vsync <= '1';
                hsync <= '1';

                data <= std_logic_vector(to_unsigned(byte_v, DATA_BITS));
 
                wait until falling_edge(clk);
                pixclk <= '0';

                if (column_counter = (IMAGE_WIDTH-1)) then
                    hsync <= '0';
                    column_counter <= 0;
                    line_counter <= line_counter + 1;

                    -- Blank region
                    for i in 0 to BLANK_REGION_CLKS-1 loop
                        wait until rising_edge(clk);
                        pixclk <= '1';
                        wait until falling_edge(clk);
                        pixclk <= '0';
                    end loop;
                else
                    column_counter <= column_counter + 1;
                end if;

                if (line_counter = (IMAGE_HEIGTH-1)) then
                    vsync <= '0';
                    line_counter <= 0;
                    assert false report "End of image reached!" severity failure;
                end if;
            end if;
        end loop;
 
        file_close(ppm_file);
    end process;
 
end behavior;
