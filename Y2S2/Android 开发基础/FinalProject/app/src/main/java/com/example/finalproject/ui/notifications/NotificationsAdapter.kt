package com.example.finalproject.ui.notifications

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.R
import com.example.finalproject.entities.Event
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

class NotificationsAdapter(private val events: List<Event>) :
    RecyclerView.Adapter<NotificationsAdapter.DaysViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): DaysViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.day_item, parent, false)
        return DaysViewHolder(view)
    }

    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: DaysViewHolder, position: Int) {
        val currentEvent = events[position]
        val currentDate = SimpleDateFormat("yyyy-MM-dd", Locale.getDefault()).format(Date(currentEvent.dateTime))
        holder.dayTextView.setText("${currentDate}: ${currentEvent.title}")
    }

    override fun getItemCount(): Int {
        return events.size
    }

    class DaysViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val dayTextView: TextView = itemView.findViewById(R.id.dayTextView)
    }
}