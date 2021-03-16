package com.example.starwarsdirectory;

import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.starwarsdirectory.data.CategoryData;
import com.example.starwarsdirectory.data.CategoryResults;
import com.example.starwarsdirectory.data.FilmsData;
import com.example.starwarsdirectory.data.FilmsResults;
import com.example.starwarsdirectory.data.LoadingStatus;
import com.example.starwarsdirectory.data.PeopleData;
import com.example.starwarsdirectory.data.PeopleResults;
import com.example.starwarsdirectory.data.PlanetsData;
import com.example.starwarsdirectory.data.PlanetsResults;
import com.example.starwarsdirectory.data.SpeciesData;
import com.example.starwarsdirectory.data.SpeciesResults;
import com.example.starwarsdirectory.data.StarshipData;
import com.example.starwarsdirectory.data.StarshipResults;
import com.example.starwarsdirectory.data.VehicleData;
import com.example.starwarsdirectory.data.VehicleResults;
import com.example.starwarsdirectory.utils.themeUtils;

import java.util.ArrayList;

public class CategoryActivity extends AppCompatActivity
        implements CategoryAdapter.OnCategoryItemClickListener {
    private final String TAG = CategoryActivity.class.getName();
    public static final String EXTRA_CATEGORYTYPE = "DisplayActivity.CategoryType";

    private TextView displayNameTV;
    private ProgressBar loadingIndicatorPB;
    private TextView errorMessageTV;
    private RecyclerView displayListRV;
    private EditText editTextSearch;
    private CategoryResults currentResults;

    private String displayName;
    private String categoryType;

    private CategoriesViewModel categoriesViewModel;
    private CategoryAdapter categoryAdapter;

    private String currentTheme;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Initialize theme for activity
        themeUtils.onCreateSetTheme(this);
        setContentView(R.layout.activity_display);
        this.currentTheme = themeUtils.getCurrentTheme();
        this.loadingIndicatorPB = findViewById(R.id.pb_loading_indicator);
        this.errorMessageTV = findViewById(R.id.tv_error_message);
        this.editTextSearch = findViewById(R.id.editTextSearch);
        this.displayListRV = findViewById(R.id.rv_display_list);
        this.displayListRV.setLayoutManager(new LinearLayoutManager(this));
        this.displayListRV.setHasFixedSize(true);

        Intent intent = getIntent();

        if (intent != null && intent.hasExtra(EXTRA_CATEGORYTYPE)) {
            this.displayName = (String)intent.getStringExtra(EXTRA_CATEGORYTYPE);
            this.displayNameTV = findViewById(R.id.tv_displayName);
            this.displayNameTV.setText("Displaying Star Wars " + displayName + " category.");
            this.categoryType = displayName.substring(0, 1).toLowerCase() + displayName.substring(1);

            ActionBar actionBar = getSupportActionBar();
            actionBar.setTitle(displayName);
            Log.d(TAG, "" + this.displayName);

            this.categoryAdapter = new CategoryAdapter(this);
            this.displayListRV.setAdapter(this.categoryAdapter);
        }


        this.categoriesViewModel = new ViewModelProvider(this).get(CategoriesViewModel.class);
        this.loadCategory(this.categoryType, 1);
        //this.loadCategory(this.categoryType, 2);

        // Categories observe functions. Add one for each new category class
        this.categoriesViewModel.getPeopleResults().observe(this, new Observer<PeopleResults>() {
            @Override
            public void onChanged(PeopleResults peopleResults) {
                if (peopleResults != null) {
                    Log.d(TAG, "Successfully retrieved peopleResults");
                    PeopleData test = peopleResults.getResults().get(0);
                    currentResults = peopleResults;
                    Log.d("PEOPLE", String.valueOf(peopleResults.getResults().size()));
                    printPerson(test);
                    categoryAdapter.updateCategoryData(peopleResults);
                }
            }
        });

        this.categoriesViewModel.getPlanetsResults().observe(this, new Observer<PlanetsResults>() {
            @Override
            public void onChanged(PlanetsResults planetsResults) {
                if (planetsResults != null) {
                    Log.d(TAG, "Successfully retrieved planetsResults");
                    PlanetsData test = planetsResults.getResults().get(0);
                    currentResults = planetsResults;
                    printPlanet(test);
                    categoryAdapter.updateCategoryData(planetsResults);
                }
            }
        });

        this.categoriesViewModel.getFilmsResults().observe(this, new Observer<FilmsResults>() {
            @Override
            public void onChanged(FilmsResults filmsResults) {
                if (filmsResults != null) {
                    Log.d(TAG, "Successfully retrieved filmsResults");
                    FilmsData test = filmsResults.getResults().get(0);
                    currentResults = filmsResults;
                    printFilms(test);
                    categoryAdapter.updateCategoryData(filmsResults);
                }
            }
        });

        this.categoriesViewModel.getSpeciesResults().observe(this, new Observer<SpeciesResults>() {
            @Override
            public void onChanged(SpeciesResults speciesResults) {
                if (speciesResults != null) {
                    Log.d(TAG, "Successfully retrieved speciesResults");
                    SpeciesData test = speciesResults.getResults().get(0);
                    currentResults = speciesResults;
                    printSpecies(test);
                    categoryAdapter.updateCategoryData(speciesResults);
                }
            }
        });

        this.categoriesViewModel.getVehicleResults().observe(this, new Observer<VehicleResults>() {
            @Override
            public void onChanged(VehicleResults vehicleResults) {
                if (vehicleResults != null) {
                    Log.d(TAG, "Successfully retrieved vehicleResults");
                    VehicleData test = vehicleResults.getResults().get(0);
                    currentResults = vehicleResults;
                    printVehicle(test);
                    categoryAdapter.updateCategoryData(vehicleResults);
                }
            }
        });

        this.categoriesViewModel.getStarshipResults().observe(this, new Observer<StarshipResults>() {
            @Override
            public void onChanged(StarshipResults starshipResults) {
                if (starshipResults != null) {
                    Log.d(TAG, "Successfully retrieved starshipResults");
                    StarshipData test = starshipResults.getResults().get(0);
                    currentResults = starshipResults;
                    printStarship(test);
                    categoryAdapter.updateCategoryData(starshipResults);
                }
            }
        });

        this.categoriesViewModel.getLoadingStatus().observe(
                this,
                new Observer<LoadingStatus>() {
                    @Override
                    public void onChanged(LoadingStatus loadingStatus) {
                        if (loadingStatus == LoadingStatus.LOADING) {
                            loadingIndicatorPB.setVisibility(View.VISIBLE);
                        } else if (loadingStatus == LoadingStatus.SUCCESS) {
                            loadingIndicatorPB.setVisibility(View.INVISIBLE);
                            //forecastListRV.setVisibility(View.VISIBLE);
                            errorMessageTV.setVisibility(View.INVISIBLE);
                        } else {
                            loadingIndicatorPB.setVisibility(View.INVISIBLE);
                            //forecastListRV.setVisibility(View.INVISIBLE);
                            errorMessageTV.setVisibility(View.VISIBLE);
                            errorMessageTV.setText(getString(R.string.loading_error, "ヽ(。_°)ノ"));
                        }
                    }
                }
        );

        editTextSearch.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                filter(s.toString());
            }
        });

    }

    private void filter(String text) {
        ArrayList<CategoryData> categoryDataList = currentResults.getResults();
        ArrayList<CategoryData> filteredData = new ArrayList<CategoryData>();
        int type = categoryDataList.get(0).getCategoryType();
        for(int i = 0; i < categoryDataList.size(); i++){
            String s = "";
            s = categoryDataList.get(i).getName();
            if (s != null && s.toLowerCase().contains(text.toLowerCase())) {
                //adding the element to filtered list
                filteredData.add(categoryDataList.get(i));
            }
        }
        switch(type){
            case 0:
                PeopleResults peopleResults = new PeopleResults();
                peopleResults.setResults(filteredData);
                categoryAdapter.updateCategoryData(peopleResults);
                break;
            case 1:
                PlanetsResults planetResults = new PlanetsResults();
                planetResults.setResults(filteredData);
                categoryAdapter.updateCategoryData(planetResults);
                break;
            case 2:
                FilmsResults filmsResults = new FilmsResults();
                filmsResults.setResults(filteredData);
                categoryAdapter.updateCategoryData(filmsResults);
                break;
            case 3:
                SpeciesResults speciesResults = new SpeciesResults();
                speciesResults.setResults(filteredData);
                categoryAdapter.updateCategoryData(speciesResults);
                break;
            case 4:
                VehicleResults vehicleResults = new VehicleResults();
                vehicleResults.setResults(filteredData);
                categoryAdapter.updateCategoryData(vehicleResults);
                break;
            case 5:
                StarshipResults starshipResults = new StarshipResults();
                starshipResults.setResults(filteredData);
                categoryAdapter.updateCategoryData(starshipResults);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        // Small fix since recreate isnt called when returning to screen
        // so when returning from settings
        if(!themeUtils.getCurrentActivity().equals(this)) {
            if(!themeUtils.getCurrentTheme().equals(this.currentTheme)) {
                themeUtils.onCreateSetTheme(this);
                themeUtils.changeTheme(themeUtils.getCurrentActivity(), themeUtils.getCurrentTheme(), categoryType, null);
            }
        }
    }

    private void loadCategory(String categoryType, Integer page) {
        if(categoryType != null) {
            this.categoriesViewModel.loadCategory(categoryType, page);
        }
    }

    // Testing data retrieved from network calls
    private void printPerson(PeopleData test){
        Log.d(TAG, "CategoryType: " + test.getCategoryType());
        Log.d(TAG, "Name: " + test.getName());
        Log.d(TAG, "Height: " + test.getHeight());
        Log.d(TAG, "Mass: " + test.getMass());
        Log.d(TAG, "Hair Color: " + test.getHairColor());
        Log.d(TAG, "Skin Color: " + test.getSkinColor());
        Log.d(TAG, "Eye Color: " + test.getEyeColor());
        Log.d(TAG, "Birth year: " + test.getBirthYear());
        Log.d(TAG, "Gender: " + test.getGender());
        Log.d(TAG, "HomeworldURL: " + test.getHomeworld());
        for(int i = 0; i < test.getFilms().size(); i++){
            Log.d(TAG, "Film " + i + ": " + test.getFilms().get(i));
        }
        for(int i = 0; i < test.getSpecies().size(); i++){
            Log.d(TAG, "Species " + i + ": " + test.getSpecies().get(i));
        }
        for(int i = 0; i < test.getVehicles().size(); i++){
            Log.d(TAG, "Vehicles " + i + ": " + test.getVehicles().get(i));
        }
        for(int i = 0; i < test.getStarships().size(); i++){
            Log.d(TAG, "Starships " + i + ": " + test.getStarships().get(i));
        }
        Log.d(TAG, "Url: " + test.getUrl());
    }

    private void printPlanet(PlanetsData test){
        Log.d(TAG, "CategoryType: " + test.getCategoryType());
        Log.d(TAG, "Name: " + test.getName());
        Log.d(TAG, "Rotation Period: " + test.getRotationPeriod());
        Log.d(TAG, "Orbital Period: " + test.getOrbitalPeriod());
        Log.d(TAG, "Diameter: " + test.getDiameter());
        Log.d(TAG, "Climate: " + test.getClimate());
        Log.d(TAG, "Gravity: " + test.getGravity());
        Log.d(TAG, "Terrain: " + test.getTerrain());
        Log.d(TAG, "Surface Water: " + test.getSurfaceWater());
        Log.d(TAG, "Population: " + test.getPopulation());
        for(int i = 0; i < test.getResidents().size(); i++){
            Log.d(TAG, "Resident " + i + ": " + test.getResidents().get(i));
        }
        for(int i = 0; i < test.getFilms().size(); i++){
            Log.d(TAG, "Film " + i + ": " + test.getFilms().get(i));
        }

        Log.d(TAG, "Url: " + test.getUrl());
    }

    private void printFilms(FilmsData test){
        Log.d(TAG, "CategoryType: " + test.getCategoryType());
        Log.d(TAG, "Title: " + test.getName());
        Log.d(TAG, "EpisodeId: " + test.getEpisodeId());
        Log.d(TAG, "OpeningCrawl: " + test.getOpeningCrawl());
        Log.d(TAG, "Director: " + test.getDirector());
        Log.d(TAG, "Producer: " + test.getProducer());
        Log.d(TAG, "ReleaseDate: " + test.getReleaseDate());
        for(int i = 0; i < test.getCharacters().size(); i++){
            Log.d(TAG, "Characters " + i + ": " + test.getCharacters().get(i));
        }
        for(int i = 0; i < test.getPlanets().size(); i++){
            Log.d(TAG, "Planets " + i + ": " + test.getPlanets().get(i));
        }
        for(int i = 0; i < test.getStarships().size(); i++){
            Log.d(TAG, "Starships " + i + ": " + test.getStarships().get(i));
        }
        for(int i = 0; i < test.getVehicles().size(); i++){
            Log.d(TAG, "Vehicles " + i + ": " + test.getVehicles().get(i));
        }
        for(int i = 0; i < test.getSpecies().size(); i++){
            Log.d(TAG, "Species " + i + ": " + test.getSpecies().get(i));
        }
        Log.d(TAG, "Url: " + test.getUrl());

    }

    private void printSpecies(SpeciesData test){
        Log.d(TAG, "CategoryType: " + test.getCategoryType());
        Log.d(TAG, "Name: " + test.getName());
        Log.d(TAG, "Classification: " + test.getClassification());
        Log.d(TAG, "Designation: " + test.getDesignation());
        Log.d(TAG, "AverageHeight: " + test.getAverageHeight());
        Log.d(TAG, "SkinColors: " + test.getSkinColors());
        Log.d(TAG, "HairColors: " + test.getHairColors());
        Log.d(TAG, "EyeColors: " + test.getEyeColors());
        Log.d(TAG, "AverageLifespan: " + test.getAverageLifespan());

        Log.d(TAG, "Language: " + test.getLanguage());
        for(int i = 0; i < test.getPeople().size(); i++){
            Log.d(TAG, "People " + i + ": " + test.getPeople().get(i));
        }
        for(int i = 0; i < test.getFilms().size(); i++){
            Log.d(TAG, "Films " + i + ": " + test.getFilms().get(i));
        }

        Log.d(TAG, "Url: " + test.getUrl());
    }
    private void printVehicle(VehicleData test){
        Log.d(TAG, "CategoryType: " + test.getCategoryType());
        Log.d(TAG, "Name: " + test.getName());
        Log.d(TAG, "Model: " + test.getModel());
        Log.d(TAG, "Manufacturer: " + test.getManufacturer());
        Log.d(TAG, "CostInCredits: " + test.getCostInCredits());
        Log.d(TAG, "Length: " + test.getLength());
        Log.d(TAG, "MaxAtmospheringSpeed: " + test.getMaxAtmospheringSpeed());
        Log.d(TAG, "Crew: " + test.getCrew());
        Log.d(TAG, "Passengers: " + test.getPassengers());
        Log.d(TAG, "CargoCapacity: " + test.getCargoCapacity());
        Log.d(TAG, "Consumables: " + test.getConsumables());
        Log.d(TAG, "VehicleClass: " + test.getVehicleClass());
        for(int i = 0; i < test.getPilots().size(); i++){
            Log.d(TAG, "Pilots " + i + ": " + test.getPilots().get(i));
        }
        for(int i = 0; i < test.getFilms().size(); i++){
            Log.d(TAG, "Films " + i + ": " + test.getFilms().get(i));
        }
        Log.d(TAG, "Url: " + test.getUrl());

    }
    private void printStarship(StarshipData test){
        Log.d(TAG, "CategoryType: " + test.getCategoryType());
        Log.d(TAG, "Name: " + test.getName());
        Log.d(TAG, "Model: " + test.getModel());
        Log.d(TAG, "Manufacturer: " + test.getManufacturer());
        Log.d(TAG, "CostInCredits: " + test.getCostInCredits());
        Log.d(TAG, "Length: " + test.getLength());
        Log.d(TAG, "MaxAtmospheringSpeed: " + test.getMaxAtmospheringSpeed());
        Log.d(TAG, "Crew: " + test.getCrew());
        Log.d(TAG, "Passengers: " + test.getPassengers());
        Log.d(TAG, "CargoCapacity: " + test.getCargoCapacity());
        Log.d(TAG, "Consumables: " + test.getConsumables());
        Log.d(TAG, "HyperdriveRating: " + test.getHyperdriveRating());
        Log.d(TAG, "MGLT: " + test.getMGLT());
        Log.d(TAG, "StarshipClass: " + test.getStarshipClass());
        for(int i = 0; i < test.getPilots().size(); i++){
            Log.d(TAG, "Pilots " + i + ": " + test.getPilots().get(i));
        }
        for(int i = 0; i < test.getFilms().size(); i++){
            Log.d(TAG, "Films " + i + ": " + test.getFilms().get(i));
        }
        Log.d(TAG, "Url: " + test.getUrl());


    }

    @Override
    public void onCategoryItemClick(CategoryData categoryData) {
        // Do detail activity
        Intent intent = new Intent(this, CategoryDetailActivity.class);
        intent.putExtra(CategoryDetailActivity.EXTRA_CATEGORY_DATA, categoryData);
        startActivity(intent);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                Intent intent = new Intent(this, SettingsActivity.class);
                startActivity(intent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
