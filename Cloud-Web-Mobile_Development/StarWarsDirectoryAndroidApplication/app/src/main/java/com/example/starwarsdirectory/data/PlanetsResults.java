package com.example.starwarsdirectory.data;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;

public class PlanetsResults extends CategoryResults {
    @SerializedName("results")
    private ArrayList<PlanetsData> planetsResultsList;
    private String next;

    public PlanetsResults(){
        this.planetsResultsList = null;
    }

    @Override
    public ArrayList<PlanetsData> getResults(){ return planetsResultsList; }

    @Override
    public void setResults(ArrayList arrayList) {
        this.planetsResultsList = arrayList;
    }

    public void joinResults(ArrayList arrayList) {
        this.planetsResultsList.addAll(arrayList);
    }
}
