//neolib.h
/*Game User/Screen Functions
 
# Project: FireFlight - ECE453
# Write by Raul Matheus Martins
# Sponsored by Plexu and CAPES - Brazil*/


#ifndef neolib_H
#define neolib_H


void writeTile(int tileId, int color);
unsigned int nextTaggedTile(int);
int connectBluART();
int run_led();
void clearAll(int , int , int );
#endif