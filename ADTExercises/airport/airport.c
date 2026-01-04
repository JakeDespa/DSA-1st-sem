#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "closedHash.h"

int main() {
    VirtualHeap virtualHeap;
    Dictionary airportDict;
    
    // Initialize the virtual heap and dictionary
    initializeVirtualHeap(virtualHeap, &airportDict);
    
    // Airport codes from the given set
    char airportCodes[][CODE_LENGTH] = {
        "JFK", "LAX", "SFO", "CDG", "LHR", "NRT",
        "ATL", "DXB", "PEK", "MIA", "SYD", "ORD"
    };
    int numCodes = sizeof(airportCodes) / sizeof(airportCodes[0]);
    
    printf("=== AIRPORT CODE LOOKUP SYSTEM ===\n");
    printf("Closed Hashing Dictionary with Progressive Overflow\n\n");
    
    // Insert all airport codes
    printf("Inserting airport codes...\n\n");
    for (int i = 0; i < numCodes; i++) {
        int hashIndex = hashFunction(airportCodes[i]);
        printf("Inserting %s (hash index: %d)... ", airportCodes[i], hashIndex);
        
        if (insert(virtualHeap, &airportDict, airportCodes[i])) {
            int actualIndex = search(virtualHeap, airportCodes[i]);
            printf("Success! Stored at index %d\n", actualIndex);
        } else {
            printf("Failed!\n");
        }
    }
    
    // Display the final state of the virtual heap
    displayVirtualHeap(virtualHeap);
    
    // Display hash indices for each code
    displayHashIndices(virtualHeap, airportCodes, numCodes);
    
    // Example: Search for a specific airport code
    printf("\n=== SEARCH EXAMPLE ===\n");
    char searchCode[CODE_LENGTH] = "JFK";
    printf("Searching for airport code: %s\n", searchCode);
    int foundIndex = search(virtualHeap, searchCode);
    
    if (foundIndex != -1) {
        printf("Code %s found at index %d\n", searchCode, foundIndex);
    } else {
        printf("Code %s not found\n", searchCode);
    }
    
    return 0;
}
