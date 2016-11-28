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
    
    if (/*num of possible moves == 0*/) {
        return 4;
    }
    
    else if(/*move == 10 || move == 20*/){
        /*place card first available*/
        return 2;
    }
    
    else{
        if(cardID.extendID == 0){   //extending trail
            if (/*size(trialList) == 0*/) {
                if (/*size(denList) > 0*/) {
                    /*place around den*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
                else{
                    /*place card first available*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
            }
            else{
                for(int i = 0; i<size(/*trailList*/);i++){
                    if (/*trail owned availble*/) {
                        trailClaimed = true;
                    }
                }
                
                if (trailClaimed == true  /*owned trail available*/){
                    return 1;
                }
                
                else{ //no trails owned
                    if (/* # of tigers > 1*/) {
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
            if (/*size(lakeList) == 0*/) {
                if (/*size(denList) > 0*/) {
                    /*place around den*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
                else{
                    /*place card first available*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
            }
            else{
                for(int i = 0; i<size(/*lakeList*/);i++){
                    if (/*lake owned availble*/) {
                        lakeClaimed = true;
                    }
                }
                
                if (lakeClaimed == true  /*owned lake available*/){
                    return 1;
                }
                
                
                else{ //no lake owned
                    if (/* # of tigers > 1*/) {
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
            if (/*size(trailList) == 0*/) {
                if (/*size(denList) > 0*/) {
                    /*place around den*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
                else{
                    /*place card first available*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
            }
            else{
                for(int i = 0; i<size(/*trailList*/);i++){
                    if (/*trail unowned availble*/) {
                        trailNotOwnedAvailable = true;
                    }
                }
                
                if (trailNotOwnedAvailable == true && /*trail is closeable*/   /*unowned trail available*/){
                    return 3;
                }
                else if(trailNotOwnedAvailable == false){
                    return 1;
                }
                else{ //trail is not owned but also not closeable
                    if (/* # of tigers > 1*/) {
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
            if (/*size(lakeList) == 0*/) {
                if (/*size(denList) > 0*/) {
                    /*place around den*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
                else{
                    /*place card first available*/
                    if (/* # of tigers > 1*/) {
                        return 3;
                    }
                    else{
                        return 1;
                    }
                }
            }
            else{
                for(int i = 0; i<size(/*lakeList*/);i++){
                    if (/*Lake unowned availble*/) {
                        lakeNotOwnedAvailable = true;
                    }
                }
                
                if (lakeNotOwnedAvailable == true && /*lake is closeable*/   /*unowned lake available*/){
                    return 3;
                }
                else if(lakeNotOwnedAvailable == false){
                    return 1;
                }
                else{ //lake is not owned but also not closeable
                    if (/* # of tigers > 1*/) {
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
