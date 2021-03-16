package com.example.starwarsdirectory.data;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;

public class StarshipResults extends CategoryResults {
    @SerializedName("results")
    private ArrayList<StarshipData> starshipResultsList;
    private String next;

    public StarshipResults(){
        this.starshipResultsList = null;
    }

    @Override
    public ArrayList<StarshipData> getResults(){ return starshipResultsList; }

    @Override
    public void setResults(ArrayList arrayList) {
        this.starshipResultsList = arrayList;
    }

    public void joinResults(ArrayList arrayList) {
        this.starshipResultsList.addAll(arrayList);
    }
}
