package com.example.starwarsdirectory;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;

import com.example.starwarsdirectory.data.FilmsResults;
import com.example.starwarsdirectory.data.LoadingStatus;
import com.example.starwarsdirectory.data.CategoriesRepository;
import com.example.starwarsdirectory.data.PeopleResults;
import com.example.starwarsdirectory.data.PlanetsResults;
import com.example.starwarsdirectory.data.SpeciesData;
import com.example.starwarsdirectory.data.SpeciesResults;
import com.example.starwarsdirectory.data.StarshipResults;
import com.example.starwarsdirectory.data.VehicleResults;

public class CategoriesViewModel extends ViewModel {
    private CategoriesRepository repository;
    private LiveData<PeopleResults> peopleResults;
    private LiveData<PlanetsResults> planetsResults;
    private LiveData<FilmsResults> filmsResults;
    private LiveData<SpeciesResults> speciesResults;
    private LiveData<VehicleResults> vehicleResults;
    private LiveData<StarshipResults> starshipResults;
    private LiveData<LoadingStatus> loadingStatus;

    // Viewmodel for categories. Add and instantiate all category results classes.
    public CategoriesViewModel() {
        this.repository = new CategoriesRepository();
        peopleResults = repository.getPeopleResults();
        planetsResults = repository.getPlanetsResults();
        filmsResults = repository.getFilmsResults();
        speciesResults = repository.getSpeciesResults();
        vehicleResults = repository.getVehicleResults();
        starshipResults = repository.getStarshipResults();
        loadingStatus = repository.getLoadingStatus();
    }

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

    public void loadCategory(String categoryName, Integer page) {

        this.repository.loadCategory(categoryName, page);
    }
}
