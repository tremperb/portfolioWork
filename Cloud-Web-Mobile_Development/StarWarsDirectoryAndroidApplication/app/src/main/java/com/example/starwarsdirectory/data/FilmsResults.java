package com.example.starwarsdirectory.data;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;

public class FilmsResults extends CategoryResults {
    @SerializedName("results")
    private ArrayList<FilmsData> filmsResultsList;

    public FilmsResults(){
        this.filmsResultsList = null;
    }

    @Override
    public ArrayList<FilmsData> getResults(){ return filmsResultsList; }

    @Override
    public void setResults(ArrayList arrayList) {
        this.filmsResultsList = arrayList;
    }

    public void joinResults(ArrayList arrayList) {
        this.filmsResultsList.addAll(arrayList);
    }
}
