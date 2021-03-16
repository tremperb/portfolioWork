package com.example.starwarsdirectory.data;

import com.google.gson.JsonArray;
import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;

import java.lang.reflect.Type;
import java.util.ArrayList;

public class VehicleData extends CategoryData {

    private int categoryType = 4;
    private String name;
    private String model;
    private String manufacturer;
    private String costInCredits;
    private String length;
    private String maxAtmospheringSpeed;
    private String crew;
    private String passengers;
    private String cargoCapacity;
    private String consumables;
    private String vehicleClass;
    private ArrayList<String> pilots;
    private ArrayList<String> films;
    private String url;

    public VehicleData(String name,
                       String model, String manufacturer, String costInCredits, String length,
                       String maxAtmospheringSpeed,
                       String crew, String passengers, String cargoCapacity, String consumables,
                       String vehicleClass,
                       ArrayList<String> pilots, ArrayList<String> films, String url){
        this.name = name;
        this.model = model;
        this.manufacturer = manufacturer;
        this.costInCredits = costInCredits;
        this.length = length;
        this.maxAtmospheringSpeed = maxAtmospheringSpeed;
        this.crew = crew;
        this.passengers = passengers;
        this.cargoCapacity = cargoCapacity;
        this.consumables = consumables;
        this.vehicleClass = vehicleClass;
        this.pilots = pilots;
        this.films = films;
        this.url = url;
    }

    public static class JsonDeserializer implements com.google.gson.JsonDeserializer<VehicleData> {
        @Override
        public VehicleData deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context) throws JsonParseException {
            JsonObject resultsObj = json.getAsJsonObject();

            String name = resultsObj.getAsJsonPrimitive("name").getAsString();
            String model = resultsObj.getAsJsonPrimitive("model").getAsString();
            String manufacturer = resultsObj.getAsJsonPrimitive("manufacturer").getAsString();
            String costInCredits = resultsObj.getAsJsonPrimitive("cost_in_credits").getAsString();
            String length = resultsObj.getAsJsonPrimitive("length").getAsString();
            String maxAtmospheringSpeed = resultsObj.getAsJsonPrimitive("max_atmosphering_speed").getAsString();
            String crew = resultsObj.getAsJsonPrimitive("crew").getAsString();
            String passengers = resultsObj.getAsJsonPrimitive("passengers").getAsString();
            String cargoCapacity = resultsObj.getAsJsonPrimitive("cargo_capacity").getAsString();
            String consumables = resultsObj.getAsJsonPrimitive("consumables").getAsString();
            String vehicleClass = resultsObj.getAsJsonPrimitive("vehicle_class").getAsString();
            JsonArray pilotsObj = resultsObj.getAsJsonArray("pilots").getAsJsonArray();
            ArrayList<String> pilotsList = convertJSONArrayToStringArrayList(pilotsObj);
            JsonArray filmsObj = resultsObj.getAsJsonArray("films").getAsJsonArray();
            ArrayList<String> filmsList = convertJSONArrayToStringArrayList(filmsObj);
            String url = resultsObj.getAsJsonPrimitive("url").getAsString();

            return new VehicleData(name, model, manufacturer, costInCredits, length, maxAtmospheringSpeed, crew, passengers, cargoCapacity, consumables, vehicleClass, pilotsList, filmsList, url);
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
    public String getModel() {
        return model;
    }

    @Override
    public String getManufacturer() {
        return manufacturer;
    }

    @Override
    public String getCostInCredits() {
        return costInCredits;
    }

    @Override
    public String getLength() {
        return length;
    }

    @Override
    public String getMaxAtmospheringSpeed() {
        return maxAtmospheringSpeed;
    }

    @Override
    public String getCrew() {
        return crew;
    }

    @Override
    public String getPassengers() {
        return passengers;
    }

    @Override
    public String getCargoCapacity() {
        return cargoCapacity;
    }

    @Override
    public String getConsumables() {
        return consumables;
    }

    @Override
    public String getVehicleClass() {
        return vehicleClass;
    }

    @Override
    public ArrayList<String> getPilots() {
        return pilots;
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
