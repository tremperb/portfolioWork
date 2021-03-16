package com.example.starwarsdirectory.data;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;

public class VehicleResults extends CategoryResults {
    @SerializedName("results")
    private ArrayList<VehicleData> vehicleResultsList;
    private String next;

    public VehicleResults(){
        this.vehicleResultsList = null;
    }

    @Override
    public ArrayList<VehicleData> getResults(){ return vehicleResultsList; }

    @Override
    public void setResults(ArrayList arrayList) {
        this.vehicleResultsList = arrayList;
    }

    public void joinResults(ArrayList arrayList) {
        this.vehicleResultsList.addAll(arrayList);
    }
}
