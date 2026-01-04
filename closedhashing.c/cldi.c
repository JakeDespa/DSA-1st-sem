#include<stdio.h>
#include<string.h>
#include "cldi.h"

String genreTable[16] = {
    "Ballad", "Pop Rock", "Pop", "R&B", "Rock", "Country Pop", "J-Pop", "K-Pop",
    "Classical", "Theater", "EDM", "OPM", "Reggae", "Dance", "Jazz", "Indie"
};

int hash(String genre) {
    int i;
    for (i = 0; i < 16; i++) {
        if (strcmp(genre, genreTable[i]) == 0) {
            return i;
        }
    }
    return -1; 
}

void insert(VirtualHeap *VH, Song song) {
    int index = hash(song.genre);
    if (index == -1) return;

    if (strcmp(VH->H[index].elem.genre, "Empty") == 0 ||
        strcmp(VH->H[index].elem.genre, "Deleted") == 0) {

        VH->H[index].elem = song;
        VH->H[index].next = -1;
    } else {
        if (VH->avail != -1) {
            int newNode = VH->avail;
            VH->avail = VH->H[newNode].next;

            VH->H[newNode].elem = song;
            VH->H[newNode].next = -1;

            int trav = index;
            while (VH->H[trav].next != -1) {
                trav = VH->H[trav].next;
            }
            VH->H[trav].next = newNode;
        }
    }
}

void deleteMember(VirtualHeap *VH, Song song) {
    int index = hash(song.genre);
    if (index == -1) return;

    int trav = index, prev = -1;
    while (trav != -1) {
        if (strcmp(VH->H[trav].elem.songName, song.songName) == 0) {
            if (trav == index) {
                if (VH->H[trav].next != -1) {
                    int promoted = VH->H[trav].next;
                    VH->H[trav].elem = VH->H[promoted].elem;
                    VH->H[trav].next = VH->H[promoted].next;

                    VH->H[promoted].next = VH->avail;
                    VH->avail = promoted;
                } else {
                    strcpy(VH->H[trav].elem.genre, "Deleted");
                    VH->H[trav].elem.songName[0] = '\0';
                    VH->H[trav].elem.singer[0] = '\0';
                }
            } else {
                VH->H[prev].next = VH->H[trav].next;
                VH->H[trav].next = VH->avail;
                VH->avail = trav;
            }
            return;
        }
        prev = trav;
        trav = VH->H[trav].next;
    }
}


int search(VirtualHeap VH, Song song) {
    int index = hash(song.genre);
    if (index == -1) return 0;

    int trav = index;
    while (trav != -1) {
        if (strcmp(VH.H[trav].elem.songName, song.songName) == 0) {
            return 1; 
        }
        trav = VH.H[trav].next;
    }
    return 0;
}