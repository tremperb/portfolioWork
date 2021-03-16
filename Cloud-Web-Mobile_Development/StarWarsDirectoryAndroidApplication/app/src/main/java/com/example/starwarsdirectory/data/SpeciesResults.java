package com.example.starwarsdirectory.data;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;

public class SpeciesResults extends CategoryResults{
    @SerializedName("results")
    private ArrayList<SpeciesData> speciesResultsList;
    private String next;

    public SpeciesResults(){
        this.speciesResultsList = null;
    }

    @Override
    public ArrayList<SpeciesData> getResults(){ return speciesResultsList; }

    @Override
    public void setResults(ArrayList arrayList) {
        this.speciesResultsList = arrayList;
    }

    public void joinResults(ArrayList arrayList) {
        this.speciesResultsList.addAll(arrayList);
    }
}
