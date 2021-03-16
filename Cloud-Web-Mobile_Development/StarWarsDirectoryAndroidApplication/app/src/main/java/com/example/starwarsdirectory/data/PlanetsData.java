package com.example.starwarsdirectory.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;

import java.lang.reflect.Type;
import java.util.ArrayList;

public class PlanetsData extends CategoryData {

    private int categoryType = 1;
    private String name;
    private String rotationPeriod;
    private String orbitalPeriod;
    private String diameter;
    private String climate;
    private String gravity;
    private String terrain;
    private String surfaceWater;
    private String population;
    private ArrayList<String> residents;
    private ArrayList<String> filmsURL;
    private String url;

    public PlanetsData(String name, String rotationPeriod, String orbitalPeriod, String diameter,
            String climate, String gravity, String terrain, String surfaceWater,
            String population, ArrayList<String> residents, ArrayList<String> filmsURL, String url){
        this.name = name;
        this.rotationPeriod = rotationPeriod;
        this.orbitalPeriod = orbitalPeriod;
        this.diameter = diameter;
        this.climate = climate;
        this.gravity = gravity;
        this.terrain = terrain;
        this.surfaceWater = surfaceWater;
        this.population = population;
        this.residents = residents;
        this.filmsURL = filmsURL;
        this.url = url;
    }

    public static class JsonDeserializer implements com.google.gson.JsonDeserializer<PlanetsData> {
        @Override
        public PlanetsData deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            JsonObject resultsObj = json.getAsJsonObject();

            String name = resultsObj.getAsJsonPrimitive("name").getAsString();
            String rotationPeriod = resultsObj.getAsJsonPrimitive("rotation_period").getAsString();
            String orbitalPeriod = resultsObj.getAsJsonPrimitive("orbital_period").getAsString();
            String diameter = resultsObj.getAsJsonPrimitive("diameter").getAsString();
            String climate = resultsObj.getAsJsonPrimitive("climate").getAsString();
            String gravity = resultsObj.getAsJsonPrimitive("gravity").getAsString();
            String terrain = resultsObj.getAsJsonPrimitive("terrain").getAsString();
            String surfaceWater = resultsObj.getAsJsonPrimitive("surface_water").getAsString();
            String population = resultsObj.getAsJsonPrimitive("population").getAsString();
            JsonArray residentsObj = resultsObj.getAsJsonArray("residents").getAsJsonArray();
            ArrayList<String> residentsList = convertJSONArrayToStringArrayList(residentsObj);
            JsonArray filmsObj = resultsObj.getAsJsonArray("films").getAsJsonArray();
            ArrayList<String> filmsList = convertJSONArrayToStringArrayList(filmsObj);
            String url = resultsObj.getAsJsonPrimitive("url").getAsString();

            return new PlanetsData(name, rotationPeriod, orbitalPeriod, diameter, climate, gravity, terrain, surfaceWater, population, residentsList, filmsList, url);
        }

        private ArrayList<String> convertJSONArrayToStringArrayList(JsonArray jArray) {
            ArrayList<String> listData = new ArrayList<String>();
            if(jArray != null){
                for(int i = 0; i < jArray.size();i++){
                    listData.add(jArray.get(i).getAsString());
                }
            }
            return listData;
        }
    }

    @Override
    public int getCategoryType() {
        return categoryType;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getRotationPeriod() {
        return rotationPeriod;
    }

    @Override
    public String getOrbitalPeriod() {
        return orbitalPeriod;
    }

    @Override
    public String getDiameter() {
        return diameter;
    }

    @Override
    public String getClimate() {
        return climate;
    }

    @Override
    public String getGravity() {
        return gravity;
    }

    @Override
    public String getTerrain() {
        return terrain;
    }

    @Override
    public String getSurfaceWater() {
        return surfaceWater;
    }

    @Override
    public String getPopulation() {
        return population;
    }

    @Override
    public ArrayList<String> getResidents() {
        return residents;
    }

    @Override
    public ArrayList<String> getFilms() {
        return filmsURL;
    }

    @Override
    public String getUrl() {
        return url;
    }
}
