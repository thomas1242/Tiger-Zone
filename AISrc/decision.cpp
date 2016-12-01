#include <iostream>
#include <string>
#inlcude "decisionHeader.h"
#include "inout.h"

using namespace std;

int Decision::makeDecision(int cardID){
    
    lakeNotOwnedAvailable = false;
    trailNotOwnedAvailable = false;
    trailClaimed = false;
    lakeClaimed = false;
    isCloseable = false;
    indexToUse = -1;
    indexMin = -1;
    minEdge = 100;
    
    if (/*num of possible moves == 0*/) {
        return 4;
    }
    
    else{
        if(cardID.extendID == 0){   //extending trail
            if (size(availTrails) == 0) {
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    /*place tiger*/
                    return 3;
                }
                else{
                    return 1;
                }

            }
            else{
                for(int i = 0; i<size(availTrails);i++){
                    if (availTrails[i].owned==true) {
                        trailClaimed = true;
                        indexToUse = i;
                        break;
                    }
                    else{
                        indexToUse=0;
                    }
                }
                
                if (trailClaimed == true ){
                    /*x*/==availTrails[indexToUse].loc[0].first;
                    /*y*/==availTrails[indexToUse].loc[0].second;
                    /*rot*/==availTrails[availTrails].rot[0];
                    return 1;
                }
                
                else{ //no trails owned
                    if (/* # of tigers > 1*/) {
                        /*x*/==availTrails[indexToUse].loc[0].first;
                        /*y*/==availTrails[indexToUse].loc[0].second;
                        /*rot*/==availTrails[availTrails].rot[0];
                        /*place tiger*/
                    return 3;
                    }
                    else{
                        /*place first available*/
                        return 1;
                    }
                }
            }

        }
        
        else if(cardID.extendID == 1){  //extending lake
            if (size(availLakes)==0) {
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    /*place tiger*/
                    return 3;
                }
                else{
                    return 1;
                }

            }
            else{
                for(int i = 0; i<size(availLakes);i++){
                    if (availLakes[i].owned == true) {
                        lakeClaimed = true;
                        indexToUse = i;
                        break;
                    }
                    else{
                        indexToUse=0;
                    }
                    
                }
                
                if (lakeClaimed == true ){
                    /*x*/==availTrails[indexToUse].loc[0].first;
                    /*y*/==availTrails[indexToUse].loc[0].second;
                    /*rot*/==availTrails[availTrails].rot[0];
                    return 1;
                }
                
                
                else{ //no lake owned
                    if (/* # of tigers > 1*/) {
                        /*x*/==availTrails[indexToUse].loc[0].first;
                        /*y*/==availTrails[indexToUse].loc[0].second;
                        /*rot*/==availTrails[availTrails].rot[0];
                        /*place tiger*/
                    return 3;
                    }
                    else{
                        /*place first available*/
                        return 1;
                    }
                }
            }
        }
        
        else if(cardID.extendID == 2){  //closing trail
            if (size(availTrails)==0) {
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    /*place tiger*/
                    return 3;
                }
                else{
                    return 1;
                }

            }
            else{
                for(int i = 0; i<size(availTrails);i++){
                    if(availTrails[i].edges<minEdge){
                        minEdge = availTrails[i].edges
                        indexMin = i;
                        if (minEdge == 1) {
                            isCloseable = true;
                            indexToUse = indexMin;
                            if (availTrails[i].owned==false) {
                                trailNotOwnedAvailable = true;
                                break;
                            }
                        }
                        else{
                            indexToUse=0;
                        }
                    }
                }
                
                if (trailNotOwnedAvailable == true && isCloseable == true ){
                    /*x*/==availTrails[indexToUse].loc[0].first;
                    /*y*/==availTrails[indexToUse].loc[0].second;
                    /*rot*/==availTrails[availTrails].rot[0];
                    /*place tiger*/
                    return 3;
                }
                else if(trailNotOwnedAvailable == false && isCloseable==true){
                    /*x*/==availTrails[indexToUse].loc[0].first;
                    /*y*/==availTrails[indexToUse].loc[0].second;
                    /*rot*/==availTrails[availTrails].rot[0];
                    return 1;
                }
                else{ //trail is not owned but also not closeable
                    if (/* # of tigers > 1*/) {
                        /*x*/==availTrails[indexToUse].loc[0].first;
                        /*y*/==availTrails[indexToUse].loc[0].second;
                        /*rot*/==availTrails[availTrails].rot[0];
                        /*place tiger*/
                    return 3;
                    }
                    else{
                        /*place first available loc*/
                        return 1;
                    }
                }
            }
        }
        
        else if(cardID.extendID == 3){  //closing lake
            if (size(availLakes)==0) {
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    /*place tiger*/
                    return 3;
                }
                else{
                    return 1;
                }

            }
            else{
                for(int i = 0; i<size(availLakes);i++){
                    if(availTrails[i].edges<minEdge){
                        minEdge = availLakes[i].edges
                        indexMin = i;
                        if (minEdge == 1) {
                            isCloseable = true;
                            indexToUse = indexMin;
                            if (availLakes[i].owned==false) {
                                trailNotOwnedAvailable = true;
                                break;
                            }
                        }
                        else{
                            indexToUse=0;
                        }
                    }
                }
                
                if (lakeNotOwnedAvailable == true && isCloseable==true){
                    /*x*/==availTrails[indexToUse].loc[0].first;
                    /*y*/==availTrails[indexToUse].loc[0].second;
                    /*rot*/==availTrails[availTrails].rot[0];
                    /*place tiger*/
                    return 3;
                }
                else if(lakeNotOwnedAvailable == false){
                    /*x*/==availTrails[indexToUse].loc[0].first;
                    /*y*/==availTrails[indexToUse].loc[0].second;
                    /*rot*/==availTrails[availTrails].rot[0];
                    return 1;
                }
                else{ //lake is not owned but also not closeable
                    if (/* # of tigers > 1*/) {
                        /*x*/==availTrails[indexToUse].loc[0].first;
                        /*y*/==availTrails[indexToUse].loc[0].second;
                        /*rot*/==availTrails[availTrails].rot[0];
                        /*place tiger*/
                    return 3;
                    }
                    else{
                        /*place first available loc*/
                        return 1;
                    }
                }
            }
        }
        
        else if(cardID.extendID == -1 && /*is den*/){
            if (/* # of tigers > 1*/) {
                /*place in first available space*/
                /*place tiger*/
                    return 3;
            }
            
            else{
                /*place in first available space*/
                return 1;
            }
        }
        
        else{
            /*place in first available space*/
            return 1;
        }
    }
}
