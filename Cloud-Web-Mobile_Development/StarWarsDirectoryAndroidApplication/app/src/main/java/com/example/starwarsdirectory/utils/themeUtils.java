package com.example.starwarsdirectory.utils;

import android.app.Activity;
import android.content.Intent;

import com.example.starwarsdirectory.CategoryActivity;
import com.example.starwarsdirectory.CategoryDetailActivity;
import com.example.starwarsdirectory.R;
import com.example.starwarsdirectory.SettingsActivity;
import com.example.starwarsdirectory.data.CategoryData;

public class themeUtils {
    private static String newTheme = "jedi";
    private static Activity currentActivity;

    /**
     * Assigns a new current theme
     * resets activity which in turn recalls the on create
     * @param activity
     * @param theme
     */
    public static void changeTheme(Activity activity, String theme, String categoryType, CategoryData categoryData) {
        // get our new theme
        newTheme = theme;

        // There are 2 ways to do this
        // the overall idea is just to start the activity again with updated theme
        // recreate works but doesn't feel as smooth
        // startactivity seems to be smoother to me

        // activity.recreate();

        // The activity needs to refresh to change theme
        activity.finish();
        // start it again
        Intent intent = new Intent(activity, activity.getClass());
        if(categoryType != null) {
            intent.putExtra(CategoryActivity.EXTRA_CATEGORYTYPE, categoryType);
        }
        if(categoryData != null) {
            intent.putExtra(CategoryDetailActivity.EXTRA_CATEGORY_DATA, categoryData);
        }
        activity.startActivity(intent);

        // Dont want any animation
        activity.overridePendingTransition(0,0);
    }

    /**
     * Must be called in on create for all activity to set the theme
     * but it has to be called before you set the content view
     * @param activity
     */
    public static void onCreateSetTheme(Activity activity) {
        currentActivity = activity;
        if(newTheme.equals("sith")) {
            activity.setTheme(R.style.Sith_Theme);
        }
        else {
            activity.setTheme(R.style.Jedi_Theme);
        }
    }

    /**
     * Get the current theme
     * dont change theme if current theme
     * @return
     */
    public static String getCurrentTheme() {
        return newTheme;
    }

    /**
     * Gets the currently activity displayed to user
     * since we reassign activity here on create
     * we can simply get the current activity to apply the theme there
     * @return
     */
    public static Activity  getCurrentActivity() {
        return currentActivity;
    }
}
