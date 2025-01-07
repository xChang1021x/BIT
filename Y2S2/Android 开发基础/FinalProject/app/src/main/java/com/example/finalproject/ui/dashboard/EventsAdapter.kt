package com.example.finalproject.ui.dashboard

import android.annotation.SuppressLint
import android.os.Build
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.CheckBox
import android.widget.TextView
import androidx.annotation.RequiresApi
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.R
import com.example.finalproject.entities.Event
import java.time.temporal.ChronoUnit
import java.util.Date
import java.time.ZoneId

class EventsAdapter(private val event: List<Event>, private val listener: MyClickListener) :
    RecyclerView.Adapter<EventsAdapter.EventViewHolder>() {

    private lateinit var itemView: View
    interface MyClickListener{
        fun onClickItem(event: Event)
        fun onLongClickItem(event: Event, position: Int)
        fun onCheckClickItem(isCheck: Boolean, event: Event)
    }

    inner class EventViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val eventTitle: TextView = itemView.findViewById(R.id.eventTitle)
        val eventDateLeft: TextView = itemView.findViewById(R.id.eventDateLeft)
        val eventStatus: CheckBox = itemView.findViewById(R.id.eventStatus)
        lateinit var currentEvent: Event
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): EventViewHolder {
        itemView = LayoutInflater.from(parent.context)
            .inflate(R.layout.event_item, parent, false)
        val holder = EventViewHolder(itemView)

        return EventViewHolder(itemView)
    }

    @SuppressLint("SetTextI18n")
    @RequiresApi(Build.VERSION_CODES.O)
    override fun onBindViewHolder(holder: EventViewHolder, position: Int) {
        val currentEvent = event[position]
        val currentTime = Date()
        val currentLocalDate = currentTime.toInstant().atZone(ZoneId.systemDefault()).toLocalDate()
        val endTime = Date(currentEvent.dateTime)
        val endLocalDate = endTime.toInstant().atZone(ZoneId.systemDefault()).toLocalDate()

        var daysBetween: Long = ChronoUnit.DAYS.between(currentLocalDate, endLocalDate)

        holder.eventTitle.text = currentEvent.title
        holder.eventStatus.isChecked = currentEvent.status
        if (daysBetween > 0) {
            holder.eventDateLeft.setText("剩余 $daysBetween 天，截止日期:${endLocalDate}")
        }
        else if (daysBetween < 0) {
            daysBetween = -daysBetween
            holder.eventDateLeft.setText("超时 $daysBetween 天，截止日期:${endLocalDate} ")
        }
        else {
            holder.eventDateLeft.setText("今天截止，截止日期:${endLocalDate}")
        }
        holder.currentEvent = currentEvent

        itemView.setOnClickListener {
            listener.onClickItem(holder.currentEvent)
        }

        itemView.setOnLongClickListener {
            listener.onLongClickItem(holder.currentEvent, holder.adapterPosition)
            true
        }

        holder.eventStatus.setOnCheckedChangeListener { buttonView, isChecked ->
            listener.onCheckClickItem(isChecked, currentEvent)
        }
    }

    override fun getItemCount(): Int {
        return event.size
    }
}
