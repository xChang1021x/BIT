package com.example.finalproject.ui.notifications

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.fragment.app.Fragment
import android.widget.CalendarView
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.R
import com.example.finalproject.database.EventsDatabase
import com.example.finalproject.entities.Event
import com.example.finalproject.ui.DatabaseViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.util.Calendar
import java.util.Date
import kotlin.collections.ArrayList

class NotificationsFragment : Fragment() {

    private lateinit var eventsDatabase: EventsDatabase
    private lateinit var eventsList: MutableList<Event>
    private lateinit var calendarView: CalendarView
    private lateinit var recyclerView: RecyclerView
    private lateinit var notificationsAdapter: NotificationsAdapter
    private val databaseViewModel: DatabaseViewModel by activityViewModels()

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_notifications, container, false)
        val backToday = view.findViewById<Button>(R.id.backToday)
        eventsDatabase = databaseViewModel.eventsDatabase

        calendarView = view.findViewById(R.id.calendarTable)
        recyclerView = view.findViewById(R.id.calendarRecycleView)
        eventsList = ArrayList<Event>()

        val currentYear = Date(calendarView.date).year
        val currentMonth = Date(calendarView.date).month
        var startDate = Date(currentYear, currentMonth, 1).time
        var endDate = Date(currentYear, currentMonth + 1, 1).time
        getEventsByTime(startDate, endDate)

        recyclerView.layoutManager = LinearLayoutManager(context)
        notificationsAdapter = NotificationsAdapter(eventsList)
        recyclerView.adapter = notificationsAdapter

        calendarView.setOnDateChangeListener { _, year, month, dayOfMonth ->
            startDate = Date(year - 1900, month, 1).time
            endDate = Date(year - 1900, month + 1, 1).time
            eventsList.clear()
            getEventsByTime(startDate, endDate)
            notificationsAdapter.notifyDataSetChanged()
        }

        backToday.setOnClickListener {
            val today = Calendar.getInstance().timeInMillis
            calendarView.date = today
        }

        return view
    }

    @SuppressLint("NotifyDataSetChanged")
    private fun getEventsByTime(startDate: Long, endDate: Long) {
        lifecycleScope.launch {
            try {
                val events = withContext(Dispatchers.IO) {
                    eventsDatabase.eventDao().getEventByTime(databaseViewModel.username, startDate, endDate)
                }

                withContext(Dispatchers.Main) {
                    eventsList.clear()
                    eventsList.addAll(events)
                    notificationsAdapter.notifyDataSetChanged()
                }
            } catch (e: Exception) {
                Log.e("MY_NOTES", "Error fetching notes", e)
            }
        }
    }

}