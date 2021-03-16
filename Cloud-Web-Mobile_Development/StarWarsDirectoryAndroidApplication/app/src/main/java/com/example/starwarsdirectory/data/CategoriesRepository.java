package com.example.starwarsdirectory.data;

import android.text.TextUtils;
import android.util.Log;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class CategoriesRepository {
    private static final String TAG = CategoriesRepository.class.getSimpleName();
    private static final String BASE_URL = "https://swapi.dev/api/";

    // Add each category results class as mutable live data
    private MutableLiveData<PeopleResults> peopleResults;
    private MutableLiveData<PlanetsResults> planetsResults;
    private MutableLiveData<FilmsResults> filmsResults;
    private MutableLiveData<SpeciesResults> speciesResults;
    private MutableLiveData<VehicleResults> vehicleResults;
    private MutableLiveData<StarshipResults> starshipResults;
    private MutableLiveData<LoadingStatus> loadingStatus;

    private String currentCategoryName;

    private StarWarsAPIService starWarsAPIService;

    private PeopleResults peopleTemp = null;
    private PlanetsResults planetTemp = null;
    //private FilmsResults filmTemp = null;
    private SpeciesResults speciesTemp = null;
    private VehicleResults vehiclesTemp = null;
    private StarshipResults starshipsTemp = null;

    //private
    private int counter = 1;
    private int maxPeople = 9;
    private int maxPlanets = 6;
    private int maxSpecies = 4;
    private int maxVehicles = 4;
    private int maxStarships = 4;

    public CategoriesRepository() {
        this.peopleResults = new MutableLiveData<>();
        this.peopleResults.setValue(null);

        this.planetsResults = new MutableLiveData<>();
        this.planetsResults.setValue(null);

        this.filmsResults = new MutableLiveData<>();
        this.filmsResults.setValue(null);

        this.speciesResults = new MutableLiveData<>();
        this.speciesResults.setValue(null);

        this.vehicleResults = new MutableLiveData<>();
        this.vehicleResults.setValue(null);

        this.starshipResults = new MutableLiveData<>();
        this.starshipResults.setValue(null);

        this.loadingStatus = new MutableLiveData<>();
        this.loadingStatus.setValue(LoadingStatus.SUCCESS);

        // Don't forget to register the JsonDeserializer() for each of the category Data classes
        Gson gson = new GsonBuilder()
                .registerTypeAdapter(PeopleData.class, new PeopleData.JsonDeserializer())
                .registerTypeAdapter(PlanetsData.class, new PlanetsData.JsonDeserializer())
                .registerTypeAdapter(FilmsData.class, new FilmsData.JsonDeserializer())
                .registerTypeAdapter(SpeciesData.class, new SpeciesData.JsonDeserializer())
                .registerTypeAdapter(VehicleData.class, new VehicleData.JsonDeserializer())
                .registerTypeAdapter(StarshipData.class, new StarshipData.JsonDeserializer())
                .create();
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(BASE_URL)
                .addConverterFactory(GsonConverterFactory.create(gson))
                .build();
        this.starWarsAPIService = retrofit.create(StarWarsAPIService.class);
    }

    // Getters for each LiveData results
    public LiveData<PeopleResults> getPeopleResults() {
        return this.peopleResults;
    }
    public LiveData<PlanetsResults> getPlanetsResults() { return this.planetsResults; }
    public LiveData<FilmsResults> getFilmsResults() { return this.filmsResults; }
    public LiveData<SpeciesResults> getSpeciesResults() { return this.speciesResults; }
    public LiveData<VehicleResults> getVehicleResults() { return this.vehicleResults; }
    public LiveData<StarshipResults> getStarshipResults() { return this.starshipResults; }

    public LiveData<LoadingStatus> getLoadingStatus() {
        return this.loadingStatus;
    }

    // Loads and executes the search for each category
    public void loadCategory(String categoryName, Integer page) {
        if (shouldFetchCategory(categoryName)) {
            Log.d(TAG, "fetching new data for category: " + categoryName);
            this.currentCategoryName = categoryName;
            // Set live data category results to null
            this.peopleResults.setValue(null);
            this.planetsResults.setValue(null);
            this.filmsResults.setValue(null);
            this.speciesResults.setValue(null);
            this.vehicleResults.setValue(null);
            this.starshipResults.setValue(null);
            this.loadingStatus.setValue(LoadingStatus.LOADING);

            // Depending on categoryName, execute different calls for different category classes
            switch(categoryName){
                case "people":
                    for(int i = 1; i <= maxPeople; i++) {
                        PeopleCategoryCall(categoryName, i);
                    }

                    break;
                case "planets":
                    for(int i = 1; i <= maxPlanets; i++) {
                        PlanetsCategoryCall(categoryName, i);
                    }
                    break;
                case "films":
                    FilmsCategoryCall(categoryName);
                    break;
                case "species":
                    for(int i = 1; i <= maxSpecies; i++) {
                        SpeciesCategoryCall(categoryName, i);
                    }
                    break;
                case "vehicles":
                    for(int i = 1; i <= maxVehicles; i++) {
                        VehicleCategoryCall(categoryName, i);
                    }

                    break;
                case "starships":
                    for(int i = 1; i <= maxStarships; i++) {
                        StarshipCategoryCall(categoryName, i);
                    }
                    break;
                default:
                    break;
            }

        } else {
            Log.d(TAG, "using cached data for category: " + categoryName);
        }
    }


    // Create a call function for each category
    private void PeopleCategoryCall(String categoryName, Integer page){
        Call<PeopleResults> req = this.starWarsAPIService.fetchPeopleCategory(categoryName, page);

        req.enqueue(new Callback<PeopleResults>() {
            @Override
            public void onResponse(Call<PeopleResults> call, Response<PeopleResults> response) {
                if (response.code() == 200) {
                    Log.d(TAG, "Getting results");
                    PeopleResults t;// = new PeopleResults();
                    t = response.body();

                    if(peopleTemp == null) {
                        peopleTemp = new PeopleResults();
                        peopleTemp.setResults(null);
                        peopleTemp = response.body();
                        //peopleResults.setValue(response.body());
                    }
                    else {
                        peopleTemp.joinResults(t.getResults());
                    }

                    // Doing -3 to go a bit faster
                    // since the rest will be at the bottom
                    // since people is a long list 
                    if(counter >= maxPeople - 3) {
                        peopleResults.setValue(peopleTemp);
                        loadingStatus.setValue(LoadingStatus.SUCCESS);
                    }
                    counter++;
                } else {
                    loadingStatus.setValue(LoadingStatus.ERROR);
                    Log.d(TAG, "unsuccessful API request: " + call.request().url());
                    Log.d(TAG, "  -- response status code: " + response.code());
                    Log.d(TAG, "  -- response: " + response.toString());
                }
            }
            @Override
            public void onFailure(Call<PeopleResults> call, Throwable t) {
                loadingStatus.setValue(LoadingStatus.ERROR);
                Log.d(TAG, "unsuccessful API request: " + call.request().url());
                t.printStackTrace();
            }
        });
    }

    private void PlanetsCategoryCall(String categoryName, Integer page){
        Call<PlanetsResults> req = this.starWarsAPIService.fetchPlanetsCategory(categoryName, page);
        req.enqueue(new Callback<PlanetsResults>() {
            @Override
            public void onResponse(Call<PlanetsResults> call, Response<PlanetsResults> response) {
                if (response.code() == 200) {
                    //planetsResults.setValue(response.body());
                    //loadingStatus.setValue(LoadingStatus.SUCCESS);

                    Log.d(TAG, "Getting results");
                    PlanetsResults t;// = new PeopleResults();
                    t = response.body();

                    if(planetTemp == null) {
                        planetTemp = new PlanetsResults();
                        planetTemp.setResults(null);
                        planetTemp = response.body();
                    }
                    else {
                        planetTemp.joinResults(t.getResults());
                    }

                    // Just to make a load a bit faster
                    if(counter >= maxPlanets) {
                        planetsResults.setValue(planetTemp);
                        loadingStatus.setValue(LoadingStatus.SUCCESS);
                    }
                    counter++;
                } else {
                    loadingStatus.setValue(LoadingStatus.ERROR);
                    Log.d(TAG, "unsuccessful API request: " + call.request().url());
                    Log.d(TAG, "  -- response status code: " + response.code());
                    Log.d(TAG, "  -- response: " + response.toString());
                }
            }
            @Override
            public void onFailure(Call<PlanetsResults> call, Throwable t) {
                loadingStatus.setValue(LoadingStatus.ERROR);
                Log.d(TAG, "unsuccessful API request: " + call.request().url());
                t.printStackTrace();
            }
        });
    }

    private void FilmsCategoryCall(String categoryName){
        Call<FilmsResults> req = this.starWarsAPIService.fetchFilmsCategory(categoryName);
        req.enqueue(new Callback<FilmsResults>() {
            @Override
            public void onResponse(Call<FilmsResults> call, Response<FilmsResults> response) {
                if (response.code() == 200) {
                    filmsResults.setValue(response.body());
                    loadingStatus.setValue(LoadingStatus.SUCCESS);
                } else {
                    loadingStatus.setValue(LoadingStatus.ERROR);
                    Log.d(TAG, "unsuccessful API request: " + call.request().url());
                    Log.d(TAG, "  -- response status code: " + response.code());
                    Log.d(TAG, "  -- response: " + response.toString());
                }
            }
            @Override
            public void onFailure(Call<FilmsResults> call, Throwable t) {
                loadingStatus.setValue(LoadingStatus.ERROR);
                Log.d(TAG, "unsuccessful API request: " + call.request().url());
                t.printStackTrace();
            }
        });
    }

    private void SpeciesCategoryCall(String categoryName, Integer page){
        Call<SpeciesResults> req = this.starWarsAPIService.fetchSpeciesCategory(categoryName, page);
        req.enqueue(new Callback<SpeciesResults>() {
            @Override
            public void onResponse(Call<SpeciesResults> call, Response<SpeciesResults> response) {
                if (response.code() == 200) {
                    //speciesResults.setValue(response.body());
                    //loadingStatus.setValue(LoadingStatus.SUCCESS);

                    Log.d(TAG, "Getting results");
                    SpeciesResults t;// = new PeopleResults();
                    t = response.body();

                    if(speciesTemp == null) {
                        speciesTemp = new SpeciesResults();
                        speciesTemp.setResults(null);
                        speciesTemp = response.body();
                    }
                    else {
                        speciesTemp.joinResults(t.getResults());
                    }

                    // Just to make a load a bit faster
                    if(counter >= maxSpecies) {
                        speciesResults.setValue(speciesTemp);
                        loadingStatus.setValue(LoadingStatus.SUCCESS);
                    }
                    counter++;
                } else {
                    loadingStatus.setValue(LoadingStatus.ERROR);
                    Log.d(TAG, "unsuccessful API request: " + call.request().url());
                    Log.d(TAG, "  -- response status code: " + response.code());
                    Log.d(TAG, "  -- response: " + response.toString());
                }
            }
            @Override
            public void onFailure(Call<SpeciesResults> call, Throwable t) {
                loadingStatus.setValue(LoadingStatus.ERROR);
                Log.d(TAG, "unsuccessful API request: " + call.request().url());
                t.printStackTrace();
            }
        });
    }

    private void VehicleCategoryCall(String categoryName, Integer page){
        Call<VehicleResults> req = this.starWarsAPIService.fetchVehicleCategory(categoryName, page);
        req.enqueue(new Callback<VehicleResults>() {
            @Override
            public void onResponse(Call<VehicleResults> call, Response<VehicleResults> response) {
                if (response.code() == 200) {
                    //vehicleResults.setValue(response.body());
                    //loadingStatus.setValue(LoadingStatus.SUCCESS);
                    Log.d(TAG, "Getting results");
                    VehicleResults t;// = new PeopleResults();
                    t = response.body();

                    if(vehiclesTemp == null) {
                        vehiclesTemp = new VehicleResults();
                        vehiclesTemp.setResults(null);
                        vehiclesTemp = response.body();
                    }
                    else {
                        vehiclesTemp.joinResults(t.getResults());
                    }

                    // Just to make a load a bit faster
                    if(counter >= maxVehicles) {
                        vehicleResults.setValue(vehiclesTemp);
                        loadingStatus.setValue(LoadingStatus.SUCCESS);
                    }
                    counter++;
                } else {
                    loadingStatus.setValue(LoadingStatus.ERROR);
                    Log.d(TAG, "unsuccessful API request: " + call.request().url());
                    Log.d(TAG, "  -- response status code: " + response.code());
                    Log.d(TAG, "  -- response: " + response.toString());
                }
            }
            @Override
            public void onFailure(Call<VehicleResults> call, Throwable t) {
                loadingStatus.setValue(LoadingStatus.ERROR);
                Log.d(TAG, "unsuccessful API request: " + call.request().url());
                t.printStackTrace();
            }
        });
    }

    private void StarshipCategoryCall(String categoryName, Integer page){
        Call<StarshipResults> req = this.starWarsAPIService.fetchStarshipCategory(categoryName, page);
        req.enqueue(new Callback<StarshipResults>() {
            @Override
            public void onResponse(Call<StarshipResults> call, Response<StarshipResults> response) {
                if (response.code() == 200) {
                    //starshipResults.setValue(response.body());
                    //loadingStatus.setValue(LoadingStatus.SUCCESS);
                    Log.d(TAG, "Getting results");
                    StarshipResults t;// = new PeopleResults();
                    t = response.body();

                    if(starshipsTemp == null) {
                        starshipsTemp = new StarshipResults();
                        starshipsTemp.setResults(null);
                        starshipsTemp = response.body();
                    }
                    else {
                        starshipsTemp.joinResults(t.getResults());
                    }

                    // Just to make a load a bit faster
                    if(counter >= maxStarships) {
                        starshipResults.setValue(starshipsTemp);
                        loadingStatus.setValue(LoadingStatus.SUCCESS);
                    }
                    counter++;
                } else {
                    loadingStatus.setValue(LoadingStatus.ERROR);
                    Log.d(TAG, "unsuccessful API request: " + call.request().url());
                    Log.d(TAG, "  -- response status code: " + response.code());
                    Log.d(TAG, "  -- response: " + response.toString());
                }
            }
            @Override
            public void onFailure(Call<StarshipResults> call, Throwable t) {
                loadingStatus.setValue(LoadingStatus.ERROR);
                Log.d(TAG, "unsuccessful API request: " + call.request().url());
                t.printStackTrace();
            }
        });
    }

    private boolean shouldFetchCategory(String categoryName) {
        /*
         * Fetch forecast if there isn't currently one stored.
         */
        PeopleResults peopleResults = this.peopleResults.getValue();
        PlanetsResults planetsResults = this.planetsResults.getValue();
        FilmsResults filmsResults = this.filmsResults.getValue();
        SpeciesResults speciesResults = this.speciesResults.getValue();
        VehicleResults vehicleResults = this.vehicleResults.getValue();
        StarshipResults starshipResults = this.starshipResults.getValue();

        if (peopleResults == null
                || planetsResults == null
                || filmsResults == null
                || speciesResults == null
                || vehicleResults == null
                || starshipResults == null) {
            return true;
        }

        /*
         * Fetch forecast if there was an error fetching the last one.
         */
        if (this.loadingStatus.getValue() == LoadingStatus.ERROR) {
            return true;
        }

        /*
         * Fetch forecast if either location or units have changed.
         */
        if (!TextUtils.equals(categoryName, this.currentCategoryName)) {
            return true;
        }

//        /*
//         * Fetch forecast if the earliest of the current forecast data is timestamped before "now".
//         */
//        if (currentForecast.getForecastDataList() != null && currentForecast.getForecastDataList().size() > 0) {
//            ForecastData firstForecastData = currentForecast.getForecastDataList().get(0);
//            if (firstForecastData.getEpoch() * 1000L < System.currentTimeMillis()) {
//                return true;
//            }
//        }

        /*
         * Otherwise, don't fetch the forecast.
         */
        return false;
    }

}
