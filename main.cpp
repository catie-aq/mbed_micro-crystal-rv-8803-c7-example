/*
 * Copyright (c) 2019, CATIE
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "micro-crystal-rv-8803-c7.h"
#include "mbed.h"

using namespace sixtron;

namespace {
#define PERIOD_MS 1000
}

static DigitalOut led1(LED1);
static I2C i2c(I2C_SDA, I2C_SCL);
static RV_8803_C7 rtc(&i2c);

time_t read_rtc(void)
{
	return rtc.get_time();
}

void write_rtc(time_t time)
{
	rtc.set_time(time);
}


// main() runs in its own thread in the OS
// (note the calls to ThisThread::sleep_for below for delays)
int main()
{
    //attach_rtc(callback(&rtc, &RV_8803_C7::get_time), callback(&rtc, &RV_8803_C7::set_time), NULL, NULL);
    attach_rtc(read_rtc, write_rtc, NULL, NULL);

    while (true) {
        led1 = !led1;
        if (led1) {
            printf("Alive!\n");
        }
        time_t seconds = time(NULL);
        printf("Time as a basic string = %s", ctime(&seconds));

        ThisThread::sleep_for(PERIOD_MS / 2);
    }
}
