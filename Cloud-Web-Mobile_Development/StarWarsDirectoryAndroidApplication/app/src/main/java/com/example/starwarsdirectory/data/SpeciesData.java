package com.example.starwarsdirectory.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;

import java.lang.reflect.Type;
import java.util.ArrayList;

public class SpeciesData extends CategoryData {

    private int categoryType = 3;
    private String name;
    private String classification;
    private String designation;
    private String averageHeight;
    private String skinColors;
    private String hairColors;
    private String eyeColors;
    private String averageLifespan;

    private String language;
    private ArrayList<String> people;
    private ArrayList<String> films;
    private String url;

    public SpeciesData(String name,
                       String classification, String designation, String averageHeight, String skinColors,
                       String hairColors,
                       String eyeColors, String averageLifespan, String language,
                       ArrayList<String> people, ArrayList<String> films, String url){
        this.name = name;
        this.classification = classification;
        this.designation = designation;
        this.averageHeight = averageHeight;
        this.skinColors = skinColors;
        this.hairColors = hairColors;
        this.eyeColors = eyeColors;
        this.averageLifespan = averageLifespan;
        this.language = language;
        this.people = people;
        this.films = films;
        this.url = url;
    }

    public static class JsonDeserializer implements com.google.gson.JsonDeserializer<SpeciesData> {
        @Override
        public SpeciesData deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            JsonObject resultsObj = json.getAsJsonObject();

            String name = resultsObj.getAsJsonPrimitive("name").getAsString();
            String classification = resultsObj.getAsJsonPrimitive("classification").getAsString();
            String designation = resultsObj.getAsJsonPrimitive("designation").getAsString();
            String averageHeight = resultsObj.getAsJsonPrimitive("average_height").getAsString();
            String skinColors = resultsObj.getAsJsonPrimitive("skin_colors").getAsString();
            String hairColors = resultsObj.getAsJsonPrimitive("hair_colors").getAsString();
            String eyeColors = resultsObj.getAsJsonPrimitive("eye_colors").getAsString();
            String averageLifespan = resultsObj.getAsJsonPrimitive("average_lifespan").getAsString();
            String language = resultsObj.getAsJsonPrimitive("language").getAsString();
            JsonArray peopleObj = resultsObj.getAsJsonArray("people").getAsJsonArray();
            ArrayList<String> peopleList = convertJSONArrayToStringArrayList(peopleObj);
            JsonArray filmsObj = resultsObj.getAsJsonArray("films").getAsJsonArray();
            ArrayList<String> filmsList = convertJSONArrayToStringArrayList(filmsObj);
            String url = resultsObj.getAsJsonPrimitive("url").getAsString();

            return new SpeciesData(name, classification, designation, averageHeight, skinColors, hairColors, eyeColors, averageLifespan, language, peopleList, filmsList, url);
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
    public String getClassification() {
        return classification;
    }

    @Override
    public String getDesignation() {
        return designation;
    }

    @Override
    public String getAverageHeight() {
        return averageHeight;
    }

    @Override
    public String getSkinColors() {
        return skinColors;
    }

    @Override
    public String getHairColors() {
        return hairColors;
    }

    @Override
    public String getEyeColors() {
        return eyeColors;
    }

    @Override
    public String getAverageLifespan() {
        return averageLifespan;
    }

    @Override
    public String getLanguage() {
        return language;
    }

    @Override
    public ArrayList<String> getPeople() {
        return people;
    }

    @Override
    public ArrayList<String> getFilms() {
        return films;
    }

    @Override
    public String getUrl() {
        return url;
    }
}
