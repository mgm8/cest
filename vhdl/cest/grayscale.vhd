--
-- grayscale.vhd
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
--! \file grayscale.vhd
--! 
--! \brief This module converts a color image to a gray scale.
--! 
--! \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
--! 
--! \version 0.1.0
--! 
--! \date 13/12/2017
--! 

library ieee;
    use ieee.std_logic_1164.all;

entity Grayscale is
    generic(
        DATA_WIDTH  : natural := 8;                                 --! Pixel width in bits.
        IMG_CHS     : natural := 3                                  --! Color image channels.
        );
    port(
        clk         : in std_logic;                                 --! Clock source.
        rst         : in std_logic;                                 --! Reset pin.
        data_in     : in std_logic_vector(DATA_WIDTH-1 downto 0);   --! Data input (n-channel color pixels).
        data_out    : out std_logic_vector(DATA_WIDTH-1 downto 0);  --! Data output (gray scale pixels).
        pixclk      : out std_logic                                 --! Pixel clock for the gray scale image.
        );
end Grayscale;

architecture behavior of Grayscale is

    signal channel_pos : natural := 0;                              --! Channel position counter.

begin
    
    process(clk)
    begin

        if rising_edge(clk) then
            pixclk <= '0';
        end if;

        if falling_edge(clk) then
            if (rst = '0') then
                channel_pos <= 0;                                   -- Resets channel position on a reset pulse.
            end if;

            if (IMG_CHS = 1) then
                data_out <= data_in;
                pixclk <= '1';
            elsif (IMG_CHS = 3) then
                if (channel_pos = 1) then
                    data_out <= data_in;
                    pixclk <= '1';
                    channel_pos <= channel_pos + 1;
                elsif (channel_pos = IMG_CHS-1) then
                    pixclk <= '0';
                    channel_pos <= 0;
                else
                    channel_pos <= channel_pos + 1;
                end if;
            end if;
        end if;
    end process;

end behavior;
