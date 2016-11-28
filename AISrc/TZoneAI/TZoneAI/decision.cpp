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
    
    if(cardID.extendID == 0){   //extending trail
        if (/*size(trialList) == 0*/) {
            if (/*size(denList) > 0*/) {
                /*place around den*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
                }
            }
            else{
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
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
                return /*place card none*/
            }
            
            else{ //no trails owned
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    /*place first available*/
                    return /*place card none*/
                }
            }
        }

    }
    
    else if(cardID.extendID == 1){  //extending lake
        if (/*size(lakeList) == 0*/) {
            if (/*size(denList) > 0*/) {
                /*place around den*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
                }
            }
            else{
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
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
                return /*place card none*/
            }
            
            
            else{ //no lake owned
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    /*place first available*/
                    return /*place card none*/
                }
            }
        }
    }
    
    else if(cardID.extendID == 2){  //closing trail
        if (/*size(trailList) == 0*/) {
            if (/*size(denList) > 0*/) {
                /*place around den*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
                }
            }
            else{
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
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
                return /*place card and tiger*/
            }
            else if(trailNotOwnedAvailable == false){
                return /*place card none*/
            }
            else{ //trail is not owned but also not closeable
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    /*place first available loc*/
                    return /*place card none*/
                }
            }
        }
    }
    
    else if(cardID.extendID == 3){  //closing lake
        if (/*size(lakeList) == 0*/) {
            if (/*size(denList) > 0*/) {
                /*place around den*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
                }
            }
            else{
                /*place card first available*/
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    return /*place card none*/
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
                return /*place card and tiger*/
            }
            else if(lakeNotOwnedAvailable == false){
                return /*place card none*/
            }
            else{ //lake is not owned but also not closeable
                if (/* # of tigers > 1*/) {
                    return /* place card and tiger*/
                }
                else{
                    /*place first available loc*/
                    return /*place card none*/
                }
            }
        }
    }
    
    else if(cardID.extendID == -1 && /*is den*/){
        if (/* # of tigers > 1*/) {
            /*place in first available space*/
            return /*place card with tiger*/
        }
        
        else{
            /*place in first available space*/
            return /*place card none*/
        }
    }
    
    else{
        /*place in first available space*/
        return /*place card none*/
    }
}
