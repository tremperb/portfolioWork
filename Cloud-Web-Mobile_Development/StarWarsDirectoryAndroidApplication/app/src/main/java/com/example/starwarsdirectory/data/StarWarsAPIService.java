package com.example.starwarsdirectory.data;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Path;
import retrofit2.http.Query;

public interface StarWarsAPIService {
    // Add one call per category results class
    @GET("{categoryName}/")
    Call<PeopleResults> fetchPeopleCategory(
            @Path("categoryName") String categoryName,
            @Query("page") Integer page
    );

    @GET("{categoryName}/")
    Call<PlanetsResults> fetchPlanetsCategory(
            @Path("categoryName") String categoryName,
            @Query("page") Integer page
    );

    @GET("{categoryName}/")
    Call<FilmsResults> fetchFilmsCategory(
            @Path("categoryName") String categoryName
    );

    @GET("{categoryName}/")
    Call<SpeciesResults> fetchSpeciesCategory(
            @Path("categoryName") String categoryName,
            @Query("page") Integer page
    );

    @GET("{categoryName}/")
    Call<VehicleResults> fetchVehicleCategory(
            @Path("categoryName") String categoryName,
            @Query("page") Integer page
    );

    @GET("{categoryName}/")
    Call<StarshipResults> fetchStarshipCategory(
            @Path("categoryName") String categoryName,
            @Query("page") Integer page
    );
}
