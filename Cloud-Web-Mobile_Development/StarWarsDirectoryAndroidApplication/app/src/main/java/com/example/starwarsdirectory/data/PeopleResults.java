package com.example.starwarsdirectory.data;

import android.util.Log;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;

public class PeopleResults extends CategoryResults {
    @SerializedName("results")
    private ArrayList<PeopleData> peopleResultsList;
    private String next;

    public PeopleResults(){
        this.peopleResultsList = null;
    }

    @Override
    public ArrayList<PeopleData> getResults(){ return peopleResultsList; }

    @Override
    public void setResults(ArrayList arrayList) {
        this.peopleResultsList = arrayList;
    }
  
    public void joinResults(ArrayList arrayList) {
        this.peopleResultsList.addAll(arrayList);
    }
}
