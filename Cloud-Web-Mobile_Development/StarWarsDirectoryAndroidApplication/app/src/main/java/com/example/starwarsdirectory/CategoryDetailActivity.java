package com.example.starwarsdirectory;

import android.content.Intent;

import android.content.res.Resources;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;

import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.example.starwarsdirectory.data.CategoryData;
import com.example.starwarsdirectory.utils.themeUtils;
import com.google.android.material.color.MaterialColors;

import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class CategoryDetailActivity extends AppCompatActivity {
    private final String TAG = CategoryDetailActivity.class.getName();
    public static final String EXTRA_CATEGORY_DATA = "CategoryDetailActivity.StarshipData";

    private CategoryData categoryData = null;

    RequestQueue queue;

    private ProgressBar loadingIndicatorPB;
    private TextView errorMessageTV;
    private LinearLayout detailResults;

    private int queryCount = 0;
    private int maxCount = 0;

    private String currentTheme;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Initialize theme for activity
        themeUtils.onCreateSetTheme(this);
        setContentView(R.layout.activity_category_detail);
        this.currentTheme = themeUtils.getCurrentTheme();

        this.loadingIndicatorPB = findViewById(R.id.pb_loading_detail_indicator);
        this.errorMessageTV = findViewById(R.id.tv_error_detail_message);
        this.detailResults = findViewById(R.id.detail_results);
        Intent intent = getIntent();
        if(intent != null && intent.hasExtra(EXTRA_CATEGORY_DATA)) {
            // Loading on create
            loadingIndicatorPB.setVisibility(View.VISIBLE);
            detailResults.setVisibility(View.INVISIBLE);
            errorMessageTV.setVisibility(View.INVISIBLE);
            //
            this.categoryData = (CategoryData)intent.getSerializableExtra(EXTRA_CATEGORY_DATA);
            TextView nameTV = findViewById(R.id.tv_detail_name);
            nameTV.setText(categoryData.getName());

            queue = Volley.newRequestQueue(this);
            switch(categoryData.getCategoryType()) {
                case 0:
                    // people
                    loadPerson();
                    break;
                case 1:
                    // planets
                    loadPlanet();
                    break;
                case 2:
                    // films
                    loadFilm();
                    break;
                case 3:
                    // species
                    loadSpecies();
                    break;
                case 4:
                    // vehicles
                    loadVehicle();
                    break;
                case 5:
                    // starships
                    loadStarship();
                    break;
                default:
                    break;
            }
        }
        else {
            loadingIndicatorPB.setVisibility(View.INVISIBLE);
            detailResults.setVisibility(View.INVISIBLE);
            errorMessageTV.setText(getString(R.string.loading_error, "ヽ(。_°)ノ"));
            errorMessageTV.setVisibility(View.VISIBLE);
        }
    }

    private void fetchExtra(String url, String title, int section) {

        // volley needs https but links are http
        url = url.substring(0, 4) + "s" + url.substring(4, url.length());
        Log.d(TAG, "Getting info for: " + url);
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        try {
                            queryCount++;
                            JSONObject o = new JSONObject(response);
                            if(title == null) {
                                if (o.has("title")) {
                                    insertSectionInfo(String.valueOf(o.get("title")), section);
                                } else {
                                    insertSectionInfo(String.valueOf(o.get("name")), section);
                                }
                            }
                            else {
                                if (o.has("title")) {
                                    insertInfo(title, String.valueOf(o.get("title")));
                                } else {
                                    insertInfo(title, String.valueOf(o.get("name")));
                                }
                            }
                            if(queryCount >= maxCount) {
                                // Got everything
                                loadingIndicatorPB.setVisibility(View.INVISIBLE);
                                detailResults.setVisibility(View.VISIBLE);
                                errorMessageTV.setVisibility(View.INVISIBLE);
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.d(TAG, "ERROR");
                loadingIndicatorPB.setVisibility(View.INVISIBLE);
                detailResults.setVisibility(View.INVISIBLE);
                errorMessageTV.setText(getString(R.string.loading_error, "ヽ(。_°)ノ"));
                errorMessageTV.setVisibility(View.VISIBLE);
            }
        });

        // Add the request to the RequestQueue.
        queue.add(stringRequest);
    }

    private void insertSectionInfo(String value, int section) {
        View linearLayout;
        if(section == 2)
            linearLayout = findViewById(R.id.detail_section_2);
        else if(section == 3)
            linearLayout = findViewById(R.id.detail_section_3);
        else if(section == 4)
            linearLayout = findViewById(R.id.detail_section_4);
        else
            linearLayout = findViewById(R.id.detail_section_5);

        // Create new linear layout for horizontal item
        LinearLayout newLayout = new LinearLayout(this);
        newLayout.setOrientation(LinearLayout.HORIZONTAL);

        newLayout.setLayoutParams(new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT));
        ((LinearLayout) linearLayout).addView(newLayout);

        TextView infoTV = new TextView(this);

        // Set text
        infoTV.setText(value);



        infoTV.setTextSize(18);

        // Set color
        int my_color = MaterialColors.getColor(linearLayout, R.attr.colorOnSecondary);
        infoTV.setTextColor(my_color);

        // Set layout params
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        infoTV.setLayoutParams(params);

        ((LinearLayout) newLayout).addView(infoTV);
    }

    private void insertInfo(String title, String value) {
        View linearLayout = findViewById(R.id.layout_detail);

        // Create new linear layout for horizontal item
        LinearLayout newLayout = new LinearLayout(this);
        newLayout.setOrientation(LinearLayout.HORIZONTAL);

        newLayout.setLayoutParams(new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT));
        ((LinearLayout) linearLayout).addView(newLayout);

        TextView titleTV = new TextView(this);
        TextView infoTV = new TextView(this);

        // Set text
        titleTV.setText(title);
        infoTV.setText(value);

        // Margin to title


        // Set title bold
        titleTV.setTypeface(null, Typeface.BOLD);

        // Set size
        titleTV.setTextSize(18);
        infoTV.setTextSize(18);

        // Set color
        int my_color = MaterialColors.getColor(linearLayout, R.attr.colorOnSecondary);
        infoTV.setTextColor(my_color);
        titleTV.setTextColor(my_color);

        // Set layout params
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        infoTV.setLayoutParams(params);

        params.rightMargin = 10;
        titleTV.setLayoutParams(params);

        ((LinearLayout) newLayout).addView(titleTV);
        ((LinearLayout) newLayout).addView(infoTV);

    }

    private void loadPerson() {
        insertInfo( this.getResources().getString(R.string.title_person_1),  String.valueOf(categoryData.getGender()));
        insertInfo( this.getResources().getString(R.string.title_person_2),  String.valueOf(categoryData.getHeight()) + " cm");
        insertInfo( this.getResources().getString(R.string.title_person_3),  String.valueOf(categoryData.getMass()) + " kg");
        insertInfo( this.getResources().getString(R.string.title_person_4),  String.valueOf(categoryData.getHairColor()));
        insertInfo( this.getResources().getString(R.string.title_person_5),  String.valueOf(categoryData.getSkinColor()));
        insertInfo( this.getResources().getString(R.string.title_person_6),  String.valueOf(categoryData.getEyeColor()));
        insertInfo( this.getResources().getString(R.string.title_person_7),  String.valueOf(categoryData.getBirthYear()));

        ArrayList<String> films = categoryData.getFilms();
        ArrayList<String> species = categoryData.getSpecies();
        ArrayList<String> vehicles = categoryData.getVehicles();
        ArrayList<String> starships = categoryData.getStarships();
        this.maxCount = 1 + films.size()+ species.size() + vehicles.size() + starships.size();
        fetchExtra(categoryData.getHomeworld(), this.getResources().getString(R.string.title_person_8), 0);

        // Section 2
        TextView sectionTwo = findViewById(R.id.section_2_header);
        sectionTwo.setText(this.getResources().getString(R.string.app_films));


        for(int i = 0; i < films.size(); i++) {
            fetchExtra(films.get(i), null, 2);
        }

        // section 3
        TextView sectionThree = findViewById(R.id.section_3_header);
        sectionThree.setText(this.getResources().getString(R.string.app_species));

        if(species.size() == 0) {
            insertSectionInfo("unknown", 3);
        }
        for(int i = 0; i < species.size(); i++) {
            fetchExtra(species.get(i), null, 3);
        }

        // section 4
        TextView sectionFour = findViewById(R.id.section_4_header);
        sectionFour.setText(this.getResources().getString(R.string.app_vehicles));
        if(vehicles.size() == 0) {
            insertSectionInfo("unknown", 4);
        }
        for(int i = 0; i < vehicles.size(); i++) {
            fetchExtra(vehicles.get(i), null, 4);
        }

        // section 5
        TextView sectionFive = findViewById(R.id.section_5_header);
        sectionFive.setText(this.getResources().getString(R.string.app_starships));
        if(starships.size() == 0) {
            insertSectionInfo("unknown", 5);
        }
        for(int i = 0; i < starships.size(); i++) {
            fetchExtra(starships.get(i), null, 5);
        }



    }

    private void loadPlanet() {
        insertInfo( this.getResources().getString(R.string.title_planet_1),  String.valueOf(categoryData.getRotationPeriod()));
        insertInfo( this.getResources().getString(R.string.title_planet_2),  String.valueOf(categoryData.getOrbitalPeriod()));
        insertInfo( this.getResources().getString(R.string.title_planet_3),  String.valueOf(categoryData.getDiameter()) + " km");
        insertInfo( this.getResources().getString(R.string.title_planet_4),  String.valueOf(categoryData.getClimate()));
        insertInfo( this.getResources().getString(R.string.title_planet_5),  String.valueOf(categoryData.getGravity()));
        insertInfo( this.getResources().getString(R.string.title_planet_6),  String.valueOf(categoryData.getTerrain()));
        insertInfo( this.getResources().getString(R.string.title_planet_7),  String.valueOf(categoryData.getSurfaceWater()));
        insertInfo( this.getResources().getString(R.string.title_planet_8),  String.valueOf(categoryData.getPopulation()));

        ArrayList<String> residents = categoryData.getResidents();
        ArrayList<String> films = categoryData.getFilms();
        this.maxCount = films.size() + residents.size();
        // residents
        // Section 2
        TextView sectionTwo = findViewById(R.id.section_2_header);
        sectionTwo.setText(this.getResources().getString(R.string.app_residents));


        for(int i = 0; i < residents.size(); i++) {
            fetchExtra(residents.get(i), null, 2);
        }

        // films
        // Section 3
        TextView sectionThree = findViewById(R.id.section_3_header);
        sectionThree.setText(this.getResources().getString(R.string.app_films));

        for(int i = 0; i < films.size(); i++) {
            fetchExtra(films.get(i), null, 3);
        }

    }

    private void loadFilm() {
        insertInfo( "",  String.valueOf(categoryData.getOpeningCrawl()));
        insertInfo( this.getResources().getString(R.string.title_film_1),  String.valueOf(categoryData.getDirector()));
        insertInfo( this.getResources().getString(R.string.title_film_2),  String.valueOf(categoryData.getProducer()));
        insertInfo( this.getResources().getString(R.string.title_film_3),  String.valueOf(categoryData.getReleaseDate()));

        ArrayList<String> characters = categoryData.getCharacters();
        ArrayList<String> planets = categoryData.getPlanets();
        ArrayList<String> vehicles = categoryData.getVehicles();
        ArrayList<String> starships = categoryData.getStarships();
        this.maxCount = characters.size() + planets.size() + vehicles.size() + starships.size();

        // characters
        // Section 2
        TextView sectionTwo = findViewById(R.id.section_2_header);
        sectionTwo.setText(this.getResources().getString(R.string.app_characters));

        for(int i = 0; i < characters.size(); i++) {
            fetchExtra(characters.get(i), null, 2);
        }

        // planets
        // Section 3
        TextView sectionThree = findViewById(R.id.section_3_header);
        sectionThree.setText(this.getResources().getString(R.string.app_planets));

        for(int i = 0; i < planets.size(); i++) {
            fetchExtra(planets.get(i), null, 3);
        }

        // section 4
        TextView sectionFour = findViewById(R.id.section_4_header);
        sectionFour.setText(this.getResources().getString(R.string.app_vehicles));
        if(vehicles.size() == 0) {
            insertSectionInfo("unknown", 4);
        }
        for(int i = 0; i < vehicles.size(); i++) {
            fetchExtra(vehicles.get(i), null, 4);
        }

        // section 5
        TextView sectionFive = findViewById(R.id.section_5_header);
        sectionFive.setText(this.getResources().getString(R.string.app_starships));
        if(starships.size() == 0) {
            insertSectionInfo("unknown", 5);
        }
        for(int i = 0; i < starships.size(); i++) {
            fetchExtra(starships.get(i), null, 5);
        }
    }

    private void loadSpecies() {
        insertInfo( this.getResources().getString(R.string.title_species_1),  String.valueOf(categoryData.getClassification()));
        insertInfo( this.getResources().getString(R.string.title_species_2),  String.valueOf(categoryData.getDesignation()));
        insertInfo( this.getResources().getString(R.string.title_species_3),  String.valueOf(categoryData.getHeight()) + " cm");
        insertInfo( this.getResources().getString(R.string.title_species_4),  String.valueOf(categoryData.getSkinColors()));
        insertInfo( this.getResources().getString(R.string.title_species_5),  String.valueOf(categoryData.getHairColors()));
        insertInfo( this.getResources().getString(R.string.title_species_6),  String.valueOf(categoryData.getEyeColors()));
        insertInfo( this.getResources().getString(R.string.title_species_7),  String.valueOf(categoryData.getAverageLifespan()) + " years");
        insertInfo( this.getResources().getString(R.string.title_species_8),  String.valueOf(categoryData.getLanguage()));

        ArrayList<String> people = categoryData.getPeople();
        ArrayList<String> films = categoryData.getFilms();
        this.maxCount = people.size() + films.size();

        // Section 2
        TextView sectionTwo = findViewById(R.id.section_2_header);
        sectionTwo.setText(this.getResources().getString(R.string.app_people));

        for(int i = 0; i < people.size(); i++) {
            fetchExtra(people.get(i), null, 2);
        }

        // films
        // Section 3
        TextView sectionThree = findViewById(R.id.section_3_header);
        sectionThree.setText(this.getResources().getString(R.string.app_films));

        for(int i = 0; i < films.size(); i++) {
            fetchExtra(films.get(i), null, 3);
        }

    }

    private void loadVehicle() {

        insertInfo( this.getResources().getString(R.string.title_vehicle_1),  String.valueOf(categoryData.getModel()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_2),  String.valueOf(categoryData.getManufacturer()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_3),  String.valueOf(categoryData.getCostInCredits()) + " credits");
        insertInfo( this.getResources().getString(R.string.title_vehicle_4),  String.valueOf(categoryData.getLength()) + " m");
        insertInfo( this.getResources().getString(R.string.title_vehicle_5),  String.valueOf(categoryData.getMaxAtmospheringSpeed()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_6),  String.valueOf(categoryData.getCrew()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_7),  String.valueOf(categoryData.getPassengers()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_8),  String.valueOf(categoryData.getCargoCapacity()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_9),  String.valueOf(categoryData.getConsumables()));
        insertInfo( this.getResources().getString(R.string.title_vehicle_10),  String.valueOf(categoryData.getVehicleClass()));

        ArrayList<String> pilots = categoryData.getPilots();
        ArrayList<String> films = categoryData.getFilms();
        this.maxCount = pilots.size() + films.size();

        // Section 2
        TextView sectionTwo = findViewById(R.id.section_2_header);
        sectionTwo.setText(this.getResources().getString(R.string.app_pilots));


        if(pilots.size() == 0) {
            insertSectionInfo("unknown", 2);
        }
        for(int i = 0; i < pilots.size(); i++) {
            fetchExtra(pilots.get(i), null, 2);
        }

        // films
        // Section 3
        TextView sectionThree = findViewById(R.id.section_3_header);
        sectionThree.setText(this.getResources().getString(R.string.app_films));

        for(int i = 0; i < films.size(); i++) {
            fetchExtra(films.get(i), null, 3);
        }
    }

    private void loadStarship() {
        insertInfo( this.getResources().getString(R.string.title_starship_1),  String.valueOf(categoryData.getModel()));
        insertInfo( this.getResources().getString(R.string.title_starship_2),  String.valueOf(categoryData.getManufacturer()));
        insertInfo( this.getResources().getString(R.string.title_starship_3),  String.valueOf(categoryData.getStarshipClass()));
        insertInfo( this.getResources().getString(R.string.title_starship_4),  String.valueOf(categoryData.getCostInCredits()) + " credits");
        insertInfo( this.getResources().getString(R.string.title_starship_5),  String.valueOf(categoryData.getLength()) + " m");
        insertInfo( this.getResources().getString(R.string.title_starship_6),  String.valueOf(categoryData.getCrew()));
        insertInfo( this.getResources().getString(R.string.title_starship_7),  String.valueOf(categoryData.getPassengers()));
        insertInfo( this.getResources().getString(R.string.title_starship_8),  String.valueOf(categoryData.getCargoCapacity()));

        ArrayList<String> pilots = categoryData.getPilots();
        ArrayList<String> films = categoryData.getFilms();
        this.maxCount = pilots.size() + films.size();

        // Section 2
        TextView sectionTwo = findViewById(R.id.section_2_header);
        sectionTwo.setText(this.getResources().getString(R.string.app_pilots));

        if(pilots.size() == 0) {
            insertSectionInfo("unknown", 2);
        }
        for(int i = 0; i < pilots.size(); i++) {
            fetchExtra(pilots.get(i), null, 2);
        }

        // films
        // Section 3
        TextView sectionThree = findViewById(R.id.section_3_header);
        sectionThree.setText(this.getResources().getString(R.string.app_films));

        for(int i = 0; i < films.size(); i++) {
            fetchExtra(films.get(i), null, 3);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        // Small fix since recreate isnt called when returning to screen
        // so when returning from settings
        if(!themeUtils.getCurrentActivity().equals(this)) {
            if (!themeUtils.getCurrentTheme().equals(this.currentTheme)) {
                themeUtils.onCreateSetTheme(this);
                themeUtils.changeTheme(themeUtils.getCurrentActivity(), themeUtils.getCurrentTheme(), null, categoryData);
            }
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.image_implicit_menu, menu);
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                onBackPressed();
                return true;
            case R.id.action_settings:
                Intent intent = new Intent(this, SettingsActivity.class);
                startActivity(intent);
                return true;
            case R.id.action_image:
                locateCategory();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();

    }
    private void locateCategory() {
        if(this.categoryData.getName() != null) {
            //https://www.google.com/search?q=luke%20skywalker&tbm=isch
            Uri uri = Uri.parse("https://www.google.com/search?&tbm=isch&q=" + Uri.encode(this.categoryData.getName()));
            Intent imgIntent = new Intent(Intent.ACTION_VIEW, uri);

            startActivity(imgIntent);
            Log.d(TAG, "Finding: " + this.categoryData.getName());
        }
    }
}
