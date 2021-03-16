package com.example.starwarsdirectory.data;

import java.io.Serializable;
import java.util.ArrayList;

import com.google.gson.JsonArray;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;

import org.json.JSONArray;
import org.json.JSONException;

import java.lang.reflect.Type;

public class PeopleData extends CategoryData implements Serializable {

    private int categoryType = 0;
    private String name;
    private String height;
    private String mass;
    private String hairColor;
    private String skinColor;
    private String eyeColor;
    private String birthYear;
    private String gender;
    private String homeworldURL;
    private ArrayList<String> filmsURL;
    private ArrayList<String> speciesURL;
    private ArrayList<String> vehiclesURL;
    private ArrayList<String> starshipsURL;
    private String url;

    public PeopleData(String name, String height, String mass, String hairColor,
            String skinColor, String eyeColor, String birthYear, String gender,
            String homeworldURL, ArrayList<String> filmsURL, ArrayList<String> speciesURL, ArrayList<String> vehiclesURL,
            ArrayList<String> starshipsURL, String url){
        this.name = name;
        this.height = height;
        this.mass = mass;
        this.hairColor = hairColor;
        this.skinColor = skinColor;
        this.eyeColor = eyeColor;
        this.birthYear = birthYear;
        this.gender = gender;
        this.homeworldURL = homeworldURL;
        this.filmsURL = filmsURL;
        this.speciesURL = speciesURL;
        this.vehiclesURL = vehiclesURL;
        this.starshipsURL = starshipsURL;
        this.url = url;
    }

    public static class JsonDeserializer implements com.google.gson.JsonDeserializer<PeopleData> {
        @Override
        public PeopleData deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            JsonObject resultsObj = json.getAsJsonObject();

            String name = resultsObj.getAsJsonPrimitive("name").getAsString();
            String height = resultsObj.getAsJsonPrimitive("height").getAsString();
            String mass = resultsObj.getAsJsonPrimitive("mass").getAsString();
            String hairColor = resultsObj.getAsJsonPrimitive("hair_color").getAsString();
            String skinColor = resultsObj.getAsJsonPrimitive("skin_color").getAsString();
            String eyeColor = resultsObj.getAsJsonPrimitive("eye_color").getAsString();
            String birthYear = resultsObj.getAsJsonPrimitive("birth_year").getAsString();
            String gender = resultsObj.getAsJsonPrimitive("gender").getAsString();
            String homeworldURL = resultsObj.getAsJsonPrimitive("homeworld").getAsString();
            JsonArray filmsObj = resultsObj.getAsJsonArray("films").getAsJsonArray();
            ArrayList<String> filmsList = convertJSONArrayToStringArrayList(filmsObj);
            JsonArray speciesObj = resultsObj.getAsJsonArray("species").getAsJsonArray();
            ArrayList<String> speciesList = convertJSONArrayToStringArrayList(speciesObj);
            JsonArray vehiclesObj = resultsObj.getAsJsonArray("vehicles").getAsJsonArray();
            ArrayList<String> vehiclesList = convertJSONArrayToStringArrayList(vehiclesObj);
                    JsonArray starshipsObj = resultsObj.getAsJsonArray("starships").getAsJsonArray();
            ArrayList<String> starshipsList = convertJSONArrayToStringArrayList(starshipsObj);
            String url = resultsObj.getAsJsonPrimitive("url").getAsString();

            return new PeopleData(name, height, mass, hairColor, skinColor, eyeColor, birthYear, gender, homeworldURL, filmsList, speciesList, vehiclesList, starshipsList, url);
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
    public String getHeight() {
        return height;
    }

    @Override
    public String getMass() {
        return mass;
    }

    @Override
    public String getHairColor() {
        return hairColor;
    }

    @Override
    public String getSkinColor() {
        return skinColor;
    }

    @Override
    public String getEyeColor() {
        return eyeColor;
    }

    @Override
    public String getBirthYear() {
        return birthYear;
    }

    @Override
    public String getGender() {
        return gender;
    }

    @Override
    public String getHomeworld() {
        return homeworldURL;
    }

    @Override
    public ArrayList<String> getFilms() {
        return filmsURL;
    }

    @Override
    public ArrayList<String> getSpecies() {
        return speciesURL;
    }

    @Override
    public ArrayList<String> getVehicles() {
        return vehiclesURL;
    }

    @Override
    public ArrayList<String> getStarships() {
        return starshipsURL;
    }

    @Override
    public String getUrl() {
        return url;
    }
}
