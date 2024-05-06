/*
Copyright (c) 2024, Vahid Mardani <vahid.mardani@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation  and/or other materials provided with the distribution.
3. Neither the names of the copyright holders nor the names of any
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef MELODY_H_
#define MELODY_H_


#define dW 2000
#define dH (dW / 2)
#define dQ (dH / 2)
#define dHQ (dQ / 2)
#define dQQ (dHQ / 2)


/*
 f ------ 2f ------- 3f ------ 4f --------- 5f --------- 6f
     oct      fifth     fourth    major 3rd    minor 3rd
*/
#define nC0 16.35
#define nC1 (nC0 * 2)
#define nC2 (nC1 * 2)
#define nC3 (nC2 * 2)
#define nC4 (nC3 * 2)
#define nC5 (nC4 * 2)
#define nC6 (nC5 * 2)
#define nC7 (nC6 * 2)

#define nCd0 17.32
#define nCd1 (nCd0 * 2)
#define nCd2 (nCd1 * 2)
#define nCd3 (nCd2 * 2)
#define nCd4 (nCd3 * 2)
#define nCd5 (nCd4 * 2)
#define nCd6 (nCd5 * 2)
#define nCd7 (nCd6 * 2)

#define nD0 18.35
#define nD1 (nD0 * 2)
#define nD2 (nD1 * 2)
#define nD3 (nD2 * 2)
#define nD4 (nD3 * 2)
#define nD5 (nD4 * 2)
#define nD6 (nD5 * 2)
#define nD7 (nD6 * 2)

#define nDd0 19.45
#define nDd1 (nDd0 * 2)
#define nDd2 (nDd1 * 2)
#define nDd3 (nDd2 * 2)
#define nDd4 (nDd3 * 2)
#define nDd5 (nDd4 * 2)
#define nDd6 (nDd5 * 2)
#define nDd7 (nDd6 * 2)

#define nE0 20.60
#define nE1 (nE0 * 2)
#define nE2 (nE1 * 2)
#define nE3 (nE2 * 2)
#define nE4 (nE3 * 2)
#define nE5 (nE4 * 2)
#define nE6 (nE5 * 2)
#define nE7 (nE6 * 2)

#define nF0 21.83
#define nF1 (nF0 * 2)
#define nF2 (nF1 * 2)
#define nF3 (nF2 * 2)
#define nF4 (nF3 * 2)
#define nF5 (nF4 * 2)
#define nF6 (nF5 * 2)
#define nF7 (nF6 * 2)

#define nFd0 23.12
#define nFd1 (nFd0 * 2)
#define nFd2 (nFd1 * 2)
#define nFd3 (nFd2 * 2)
#define nFd4 (nFd3 * 2)
#define nFd5 (nFd4 * 2)
#define nFd6 (nFd5 * 2)
#define nFd7 (nFd6 * 2)

#define nG0 24.50
#define nG1 (nG0 * 2)
#define nG2 (nG1 * 2)
#define nG3 (nG2 * 2)
#define nG4 (nG3 * 2)
#define nG5 (nG4 * 2)
#define nG6 (nG5 * 2)
#define nG7 (nG6 * 2)

#define nGd0 25.96
#define nGd1 (nGd0 * 2)
#define nGd2 (nGd1 * 2)
#define nGd3 (nGd2 * 2)
#define nGd4 (nGd3 * 2)
#define nGd5 (nGd4 * 2)
#define nGd6 (nGd5 * 2)
#define nGd7 (nGd6 * 2)

#define nA0 27.50
#define nA1 (nA0 * 2)
#define nA2 (nA1 * 2)
#define nA3 (nA2 * 2)
#define nA4 (nA3 * 2)
#define nA5 (nA4 * 2)
#define nA6 (nA5 * 2)
#define nA7 (nA6 * 2)

#define nAd0 29.14
#define nAd1 (nAd0 * 2)
#define nAd2 (nAd1 * 2)
#define nAd3 (nAd2 * 2)
#define nAd4 (nAd3 * 2)
#define nAd5 (nAd4 * 2)
#define nAd6 (nAd5 * 2)
#define nAd7 (nAd6 * 2)

#define nB0 30.87
#define nB1 (nB0 * 2)
#define nB2 (nB1 * 2)
#define nB3 (nB2 * 2)
#define nB4 (nB3 * 2)
#define nB5 (nB4 * 2)
#define nB6 (nB5 * 2)
#define nB7 (nB6 * 2)


struct note {
    int tone;
    int duration;
};


void
play(int pin, struct note *melody, volatile bool *more) {
    int i = 0;
    int s;
    int dur;
    struct note *n;

    while (*more) {
        n = &melody[i++];
        if (!n->duration) {
            break;
        }
        tone(pin, n->tone);
        dur = (int) n->duration;
        while (*more && dur) {
            s = min(dur, 50);
            delay(s);
            dur -= s;
        }
        noTone(pin);
    }
}


static struct note greeting_melody[] = {
    {nE4, dQ},
    {nA4, dQ},
    {nC5, dQ},
    {nB4, dQ},
    {nA4, dH},
    {nC5, dHQ},
    {nA4, dQ},
    {nB4, dQ},
    {nA4, dQ},
    {nF4, dQ},
    {nG4, dQ},
    {nE4, dH},
    {0, 0}
};


static struct note programfinish_melody[] = {
    {nD3, dQ},
    {nA3, dQ},
    {nD4, dQ},
    {nF4, dQ},
    {0, 0}
};


#endif  // MELODY_H_
