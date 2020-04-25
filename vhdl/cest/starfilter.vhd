--
-- starfilter.vhd
-- 
-- Copyright (C) 2017-2019, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
-- 
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
-- 
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
-- 
-- You should have received a copy of the GNU General Public License
-- along with this program. If not, see <http://www.gnu.org/licenses/>.
-- 
-- 

--! 
--! \brief Star pixels filter for a star tracker simulation.
--! 
--! \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
--! 
--! \version 1.0
--! 
--! \date 13/12/2017
--! 

library ieee;
    use ieee.std_logic_1164.all;
    use ieee.math_real.all;

entity StarFilter is
    generic(
        STAR_THRESHOLD_VAL : natural := 150
        );
end StarFilter;

architecture behavior of StarFilter is

    component Clock is
        port(
            clk         : out std_logic
            );
    end component;

    component Sensor is
        generic(
            DATA_BITS   : natural := 8;                                 --! Pixel size in bits (Sensor dependent).
            CHANNELS    : natural := 3                                  --! Pixel channels.
            );
        port(
            clk         : in std_logic;                                 --! Clock source.
            rst         : in std_logic;                                 --! Reset pin.
            pixclk      : out std_logic;                                --! Pixel clock.
            hsync       : out std_logic;                                --! Horizontal sync.
            vsync       : out std_logic;                                --! Vertical sync.
            data        : out std_logic_vector(DATA_BITS-1 downto 0)    --! Data output.
            );
    end component;

    component Grayscale is
        generic(
            DATA_WIDTH  : natural := 8;
            IMG_CHS     : natural := 3
            );
        port(
            clk         : in std_logic;
            rst         : in std_logic;
            data_in     : in std_logic_vector(DATA_WIDTH-1 downto 0);
            data_out    : out std_logic_vector(DATA_WIDTH-1 downto 0);
            pixclk      : out std_logic
            );
    end component;

    component Threshold is 
        generic(
            DATA_WIDTH  : natural := 8;                                 --! Pixel width in bits.
            TH_VALUE    : natural := 200                                --! Threshold value (0 to 255).
            );
        port(
            clk         : in std_logic;                                 --! Clock source.
            en          : in std_logic;                                 --! Enable signal (Activation "clock").
            data_in     : in std_logic_vector(DATA_WIDTH-1 downto 0);   --! Data input (gray scale pixels).
            data_out    : out std_logic_vector(DATA_WIDTH-1 downto 0);  --! Data output (above threshold pixels).
            pixclk      : out std_logic                                 --! Signalizes when to pick the data from the output.
            );
    end component;

    component Counter is
        generic(
            UPPER_LIMIT : natural := 64;                                                            --! Upper counting limit (Max. value).
            INIT_VALUE  : natural := 0                                                              --! Initial value.
            );
        port(
            clk         : in std_logic;                                                             --! Reference clock.
            en          : in std_logic;                                                             --! Enable signal.
            dir         : in std_logic;                                                             --! Counting direction ('1' = up, '0' = down).
            rst         : in std_logic;                                                             --! Resets counting (go back to 0).
            output      : out std_logic_vector(natural(ceil(log2(real(UPPER_LIMIT))))-1 downto 0)   --! Counter output.
            );
    end component;

    component Log is
        generic(
            DATA_BITS   : natural := 8;                                     --! Length of the pixel data.
            X_POS_BITS  : natural := 8;                                     --! Length of the x position data.
            Y_POS_BITS  : natural := 8;                                     --! Length of the y position data.
            PRINT_DATA  : boolean := FALSE;                                 --! TRUE/FALSE to print the log data on the screen.
            FILE_NAME   : string := "star_pixels.csv"                       --! Output log file name.
            );
        port(
            log_data    : in std_logic;                                     --! Enables a log line writing.
            x_pos       : in std_logic_vector(X_POS_BITS-1 downto 0);       --! x position of the pixels values.
            y_pos       : in std_logic_vector(Y_POS_BITS-1 downto 0);       --! y position of the pixels values.
            pix_val     : in std_logic_vector(DATA_BITS-1 downto 0)         --! Pixel value in the (x,y) position.
            );
    end component;

    -- ************* CONFIGURATION PARAMETERS *************
    constant PIXEL_BITS         : natural := 8;
    constant IMAGE_CHANNELS     : natural := 1;
    constant IMG_MAX_LENGTH     : natural := 800;
    constant IMG_MAX_HEIGHT     : natural := 600;
    constant MAX_CENTROIDS      : natural := 256;
    constant MAX_PIX_PER_STAR   : natural := 100;

    signal master_clk       : std_logic;
    signal pixel_clk        : std_logic;
    signal gray_clk         : std_logic;
    signal thresh_clk       : std_logic;
    signal raw_pixel        : std_logic_vector(PIXEL_BITS-1 downto 0);
    signal gray_pixel       : std_logic_vector(PIXEL_BITS-1 downto 0);
    signal h_ref            : std_logic;
    signal v_ref            : std_logic;
    signal memory_pos       : std_logic_vector(natural(ceil(log2(real(MAX_CENTROIDS))))-1 downto 0);
    signal i_pos            : std_logic_vector(natural(ceil(log2(real(IMG_MAX_LENGTH))))-1 downto 0);
    signal j_pos            : std_logic_vector(natural(ceil(log2(real(IMG_MAX_HEIGHT))))-1 downto 0);
    signal star_px_val      : std_logic_vector(PIXEL_BITS-1 downto 0);

begin

    MASTER_CLOCK : Clock    port map(clk => master_clk);

    IMAGE_SENSOR : Sensor   generic map(
                                DATA_BITS => PIXEL_BITS,
                                CHANNELS => IMAGE_CHANNELS
                                )
                            port map(
                                clk => master_clk,
                                rst => master_clk,
                                pixclk => pixel_clk,
                                hsync => h_ref,
                                vsync => v_ref,
                                data => raw_pixel
                                );

    GRAY_CONV : Grayscale   generic map(
                                DATA_WIDTH => PIXEL_BITS,
                                IMG_CHS => IMAGE_CHANNELS
                                )
                            port map(
                                clk => pixel_clk,
                                rst => '1',
                                data_in => raw_pixel,
                                data_out => gray_pixel,
                                pixclk => gray_clk
                                );

    TH_FILTER : Threshold   generic map(
                                DATA_WIDTH => PIXEL_BITS,
                                TH_VALUE => STAR_THRESHOLD_VAL
                                )
                            port map(
                                clk => pixel_clk,
                                en => gray_clk,
                                data_in => gray_pixel,
                                data_out => star_px_val,
                                pixclk => thresh_clk
                                );

    X_AX_COUNTER : Counter  generic map(
                                UPPER_LIMIT => IMG_MAX_LENGTH-1,
                                INIT_VALUE  => 799
                                )
                            port map(
                                clk     => pixel_clk,
                                en      => h_ref,
                                dir     => '1',
                                rst     => h_ref,
                                output  => i_pos
                                );

    Y_AX_COUNTER : Counter  generic map(
                                UPPER_LIMIT => IMG_MAX_HEIGHT,
                                INIT_VALUE  => 0
                                )
                            port map(
                                clk     => h_ref,
                                en      => v_ref,
                                dir     => '1',
                                rst     => v_ref,
                                output  => j_pos
                                );

    BIN_LOG : Log           generic map(
                                DATA_BITS   => PIXEL_BITS,
                                X_POS_BITS  => natural(ceil(log2(real(IMG_MAX_LENGTH)))),
                                Y_POS_BITS  => natural(ceil(log2(real(IMG_MAX_HEIGHT)))),
                                PRINT_DATA  => FALSE,
                                FILE_NAME   => "/tmp/star_pixels.csv"
                                )
                            port map(
                                log_data    => thresh_clk,
                                x_pos       => i_pos,
                                y_pos       => j_pos,
                                pix_val     => star_px_val
                                );

end behavior;
