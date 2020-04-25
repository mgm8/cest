--
-- counter.vhd
-- 
-- Copyright (C) 2018-2019, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
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
--! \brief Up/Down counter.
--! 
--! \details Reference: https://startingelectronics.org/software/VHDL-CPLD-course/tut19-up-down-counter/
--! 
--! \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
--! 
--! \version 0.1.0
--! 
--! \date 24/01/2018
--!

library ieee;
    use ieee.std_logic_1164.all;
    use ieee.math_real.all;
    use ieee.numeric_std.all;

entity Counter is
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
end Counter;

architecture behavior of Counter is

    signal count : natural := INIT_VALUE;

begin

    process(clk)
    begin
        if falling_edge(clk) then
            if (rst = '0') then
                count <= INIT_VALUE;
            else
                if (en = '1') then
                    if (dir = '1') then
                        -- Counts up to limit, then stop
                        if (count /= UPPER_LIMIT) then
                            count <= count + 1;   -- Count up
                        elsif (count = UPPER_LIMIT) then
                            count <= 0;
                        end if;
                    else
                        -- Counts down to 0, then stop
                        if (count /= 0) then
                            count <= count - 1;   -- Count down
                        elsif (count = 0) then
                            count <= UPPER_LIMIT;
                        end if;
                    end if;
                end if;
            end if;
        end if;
    end process;

    output <= std_logic_vector(to_unsigned(count, output'length));

end behavior;
