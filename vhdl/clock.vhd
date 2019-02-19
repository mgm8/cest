--
-- clock.vhd
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
--! \brief Clock generation block for simulation.
--! 
--! \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
--! 
--! \version 0.1.0
--! 
--! \date 13/12/2017
--! 

library ieee;
    use ieee.std_logic_1164.all;

entity Clock is
    port(
        clk : out std_logic
        );
end Clock;

architecture behavior of Clock is

    signal clock_signal : std_logic := '0';

    begin

    clock_signal <= not (clock_signal) after 10 ns;     -- Clock with 20 ns time period

    clk <= clock_signal;

end behavior;
