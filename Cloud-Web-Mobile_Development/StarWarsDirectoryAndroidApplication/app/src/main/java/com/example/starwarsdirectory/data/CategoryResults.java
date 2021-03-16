package com.example.starwarsdirectory.data;

import java.util.ArrayList;

public abstract class CategoryResults<CategoryData> {

    public abstract ArrayList<CategoryData> getResults();

    public abstract void setResults(ArrayList<CategoryData> data);
}
