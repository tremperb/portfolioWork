package com.example.starwarsdirectory;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.starwarsdirectory.data.CategoryData;
import com.example.starwarsdirectory.data.CategoryResults;

public class CategoryAdapter extends RecyclerView.Adapter<CategoryAdapter.CategoryItemViewHolder> {
    private final String TAG = CategoryAdapter.class.getName();

    private CategoryResults categoryResults;
    private OnCategoryItemClickListener onCategoryItemClickListener;

    public interface OnCategoryItemClickListener {
        void onCategoryItemClick(CategoryData categoryData);
    }

    public CategoryAdapter(OnCategoryItemClickListener onCategoryItemClickListener) {
        this.onCategoryItemClickListener = onCategoryItemClickListener;
    }

    @NonNull
    @Override
    public CategoryItemViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View itemView = inflater.inflate(R.layout.category_list_item, parent, false);
        return new CategoryItemViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull CategoryItemViewHolder holder, int position) {
        CategoryData categoryData = (CategoryData)this.categoryResults.getResults().get(position);
        holder.bind(categoryData);
    }

    @Override
    public int getItemCount() {
        if(this.categoryResults == null || this.categoryResults.getResults() == null) {
            return 0;
        }
        else {
            return this.categoryResults.getResults().size();
        }
    }

    public void updateCategoryData(CategoryResults categoryResults) {
        this.categoryResults = categoryResults;
        notifyDataSetChanged();
    }


    class CategoryItemViewHolder extends RecyclerView.ViewHolder {
        final private TextView nameTV;

        public CategoryItemViewHolder(View itemView) {
            super(itemView);
            nameTV = itemView.findViewById(R.id.tv_starship_name);

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    onCategoryItemClickListener.onCategoryItemClick(
                            (CategoryData)categoryResults.getResults().get(getAdapterPosition())
                    );
                }
            });
        }

        public void bind(CategoryData categoryData) {
            Context ctx = this.itemView.getContext();
            // Set text

            Log.d(TAG, "binding: " + categoryData.getName());
            nameTV.setText(categoryData.getName());


        }
    }

}
