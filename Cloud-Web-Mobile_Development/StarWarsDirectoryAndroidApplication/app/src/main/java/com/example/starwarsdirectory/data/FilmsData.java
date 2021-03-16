package com.example.starwarsdirectory.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;

import java.lang.reflect.Type;
import java.util.ArrayList;

public class FilmsData extends CategoryData {

    private int categoryType = 2;
    private String title;
    private int episodeId;
    private String openingCrawl;
    private String director;
    private String producer;
    private String releaseDate;
    private ArrayList<String> characters;
    private ArrayList<String> planets;
    private ArrayList<String> starships;
    private ArrayList<String> vehicles;
    private ArrayList<String> species;
    private String url;

    public FilmsData(String title, int episodeId,
                     String openingCrawl, String director, String producer, String releaseDate,
                     ArrayList<String> characters, ArrayList<String> planets,
                     ArrayList<String> starships, ArrayList<String> vehicles,
                     ArrayList<String> species, String url){
        this.title = title;
        this.episodeId = episodeId;
        this.openingCrawl = openingCrawl;
        this.director = director;
        this.producer = producer;
        this.releaseDate = releaseDate;
        this.characters = characters;
        this.planets = planets;
        this.starships = starships;
        this.vehicles = vehicles;
        this.species = species;
        this.url = url;
    }

    public static class JsonDeserializer implements com.google.gson.JsonDeserializer<FilmsData> {
        @Override
        public FilmsData deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            JsonObject resultsObj = json.getAsJsonObject();

            String title = resultsObj.getAsJsonPrimitive("title").getAsString();
            int episodeId = resultsObj.getAsJsonPrimitive("episode_id").getAsInt();
            String openingCrawl = resultsObj.getAsJsonPrimitive("opening_crawl").getAsString();
            String director = resultsObj.getAsJsonPrimitive("director").getAsString();
            String producer = resultsObj.getAsJsonPrimitive("producer").getAsString();
            String releaseDate = resultsObj.getAsJsonPrimitive("release_date").getAsString();
            JsonArray charactersObj = resultsObj.getAsJsonArray("characters").getAsJsonArray();
            ArrayList<String> charactersList = convertJSONArrayToStringArrayList(charactersObj);
            JsonArray planetsObj = resultsObj.getAsJsonArray("planets").getAsJsonArray();
            ArrayList<String> planetsList = convertJSONArrayToStringArrayList(planetsObj);
            JsonArray starshipsObj = resultsObj.getAsJsonArray("starships").getAsJsonArray();
            ArrayList<String> starshipsList = convertJSONArrayToStringArrayList(starshipsObj);
            JsonArray vehiclesObj = resultsObj.getAsJsonArray("vehicles").getAsJsonArray();
            ArrayList<String> vehiclesList = convertJSONArrayToStringArrayList(vehiclesObj);
            JsonArray speciesObj = resultsObj.getAsJsonArray("species").getAsJsonArray();
            ArrayList<String> speciesList = convertJSONArrayToStringArrayList(speciesObj);
            String url = resultsObj.getAsJsonPrimitive("url").getAsString();

            return new FilmsData(title, episodeId, openingCrawl, director, producer, releaseDate, charactersList, planetsList, starshipsList, vehiclesList, speciesList, url);
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
    public String getName() {
        return title;
    }

    @Override
    public int getEpisodeId() {
        return episodeId;
    }

    @Override
    public String getOpeningCrawl() {
        return openingCrawl;
    }

    @Override
    public String getDirector() {
        return director;
    }

    @Override
    public String getProducer() {
        return producer;
    }

    @Override
    public String getReleaseDate() {
        return releaseDate;
    }

    @Override
    public ArrayList<String> getCharacters() {
        return characters;
    }

    @Override
    public ArrayList<String> getPlanets() {
        return planets;
    }

    @Override
    public ArrayList<String> getStarships() {
        return starships;
    }

    @Override
    public ArrayList<String> getVehicles() {
        return vehicles;
    }

    @Override
    public ArrayList<String> getSpecies() {
        return species;
    }

    @Override
    public int getCategoryType() {
        return categoryType;
    }

    @Override
    public String getUrl() {
        return url;
    }
}
