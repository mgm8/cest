/*
 * cdpu.h
 * 
 * Copyright (C) 2018, Gabriel Mariano Marcelino <gabriel.mm8@gmail.comk>
 * 
 * This program is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief CentroiD Processor Unit class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 05/03/2018
 * 
 * \addtogroup cdpu
 * \{
 */

#include "cdpu.h"

using namespace st;

CDPU::CDPU()
{
    this->centroid.x        = 0;
    this->centroid.y        = 0;
    this->centroid.value    = 0;
    this->centroid.pixels   = 0;
    this->pixels            = 0;
    this->K                 = 1;
}

CDPU::~CDPU()
{

}

void CDPU::Update(unsigned int x_new, unsigned int y_new, uint8_t color_new, float gain)
{
    if (this->DistanceFrom(x_new, y_new) < DISTANCE_THRESHOLD_MAN)
    {
        this->K *= gain;
        this->centroid.value = (this->K*this->centroid.value) + ((1-this->K)*color_new);
        this->centroid.x = (this->K*this->centroid.x) + ((1-this->K)*x_new);
        this->centroid.y = (this->K*this->centroid.y) + ((1-this->K)*y_new);
        this->centroid.pixels++;

        this->pixels++;
    }
}

void CDPU::SetCentroid(unsigned int x_new, unsigned int y_new, uint8_t color_new)
{
    this->centroid.x = x_new;
    this->centroid.y = y_new;
    this->centroid.value += color_new;
    this->centroid.pixels = 1;
}

Centroid CDPU::GetCentroid()
{
    return this->centroid;
}

float CDPU::DistanceFrom(unsigned int x_comp, unsigned int y_comp)
{
    return abs(this->centroid.x - x_comp) + abs(this->centroid.y - y_comp);
}

uint8_t CDPU::GetPixels()
{
    return this->pixels;
}

//! \} End of cdpu group
