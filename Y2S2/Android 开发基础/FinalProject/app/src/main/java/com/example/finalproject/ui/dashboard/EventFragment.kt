package com.example.finalproject.ui.dashboard

import android.annotation.SuppressLint
import android.app.AlertDialog
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.MenuItem
import android.view.View
import android.view.ViewGroup
import android.widget.DatePicker
import android.widget.EditText
import android.widget.PopupMenu
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.R
import com.example.finalproject.database.EventsDatabase
import com.example.finalproject.databinding.FragmentDashboardBinding
import com.example.finalproject.entities.Event
import com.example.finalproject.ui.DatabaseViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.util.Date

class EventFragment : Fragment(), EventsAdapter.MyClickListener {

    private var _binding: FragmentDashboardBinding? = null
    private lateinit var eventsDatabase: EventsDatabase
    private lateinit var eventsRecyclerView: RecyclerView
    private lateinit var eventsAdapter: EventsAdapter
    private lateinit var eventsList: MutableList<Event>
    private val databaseViewModel: DatabaseViewModel by activityViewModels()
    private val binding get() = _binding!!
    @SuppressLint("NotifyDataSetChanged")
    override fun onClickItem(event: Event) {
        val builder = AlertDialog.Builder(requireContext())
        val dialogView = layoutInflater.inflate(R.layout.dialog_add_task, null)
        val titleEditText = dialogView.findViewById<EditText>(R.id.edit_text_title)
        val datePicker = dialogView.findViewById<DatePicker>(R.id.date_picker)

        titleEditText.setText(event.title)
        builder.setView(dialogView)
            .setPositiveButton("Save") { dialog, which ->
                val year = datePicker.year - 1900
                val month = datePicker.month
                val day = datePicker.dayOfMonth

                event.title = titleEditText.text.toString()
                event.dateTime = Date(year, month, day).time
                lifecycleScope.launch {
                    eventsDatabase.eventDao().update(event)
                }
                eventsAdapter.notifyDataSetChanged()
            }
            .setNegativeButton("Cancel") { dialog, which ->
                dialog.dismiss()
            }
            .show()
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onLongClickItem(event: Event, position: Int) {
        AlertDialog.Builder(requireContext())
            .setMessage("你要删除这个事件吗？")
            .setPositiveButton("OK"){ _, which ->
                deleteEvent(event)
                eventsAdapter.notifyItemRemoved(position)
                eventsList.removeAt(position)
            }
            .setNegativeButton("cancel"){ _, which ->
            }
            .create()
            .show()
    }

    override fun onCheckClickItem(isCheck: Boolean, event: Event) {
        event.status = isCheck
        lifecycleScope.launch {
            databaseViewModel.eventsDatabase.eventDao().update(event)
        }

    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentDashboardBinding.inflate(inflater, container, false)
        val root: View = binding.root
        eventsDatabase = databaseViewModel.eventsDatabase
        return root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        eventsRecyclerView = binding.recyclerViewEvents.findViewById(R.id.recyclerView_events)
        val linearLayoutManager = LinearLayoutManager(requireContext())
        eventsRecyclerView.layoutManager = linearLayoutManager

        eventsList = ArrayList<Event>()

        getEvents()

        eventsAdapter = EventsAdapter(eventsList, this)
        eventsRecyclerView.adapter = eventsAdapter

        binding.addTask.setOnClickListener{
            showAddTaskDialog()
        }

        binding.moreSetting.setOnClickListener {
            showPopupMenu(it)
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    @SuppressLint("NotifyDataSetChanged")
    private fun showPopupMenu(view: View) {
        val popupMenu = PopupMenu(requireContext(), view)
        popupMenu.menuInflater.inflate(R.menu.more_menu, popupMenu.menu)
        popupMenu.setOnMenuItemClickListener { menuItem: MenuItem ->
            when (menuItem.itemId) {
                R.id.clearData -> {
                    AlertDialog.Builder(requireContext())
                        .setMessage("你确定要清除所有事件吗？")
                        .setPositiveButton("OK") { _, _ ->
                            lifecycleScope.launch {
                                databaseViewModel.eventsDatabase.eventDao().clearUserEvents(databaseViewModel.username)
                                eventsList.clear()
                                eventsAdapter.notifyDataSetChanged()
                                refreshFragment()
                            }
                        }
                        .setNegativeButton("cancel") { _, _ -> }
                        .create()
                        .show()
                    true
                }
                R.id.refresh -> {
                    refreshFragment()
                    true
                }
                else -> false
            }
        }
        popupMenu.show()
    }

    private fun refreshFragment() {
        val fragmentTransaction = parentFragmentManager.beginTransaction()
        fragmentTransaction.detach(this).attach(this).commit()
    }

    private fun deleteEvent(event: Event) {
        lifecycleScope.launch {
            try {
                eventsDatabase.eventDao().deleteEvent(event)
            } catch (e: Exception) {
                Log.e("DELETE_EVENTS", "Error Delete Event", e)
            }
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    private fun showAddTaskDialog() {
        val builder = AlertDialog.Builder(requireContext())
        val dialogView = layoutInflater.inflate(R.layout.dialog_add_task, null)
        val titleEditText = dialogView.findViewById<EditText>(R.id.edit_text_title)
        val datePicker = dialogView.findViewById<DatePicker>(R.id.date_picker)

        builder.setView(dialogView)
            .setPositiveButton("Add") { dialog, which ->
                val year = datePicker.year - 1900
                val month = datePicker.month
                val day = datePicker.dayOfMonth
                val event = Event().apply {
                    title = titleEditText.text.toString()
                    dateTime = Date(year, month, day).time
                    user = databaseViewModel.username
                }
                saveEventToDatabase(event)
                eventsAdapter.notifyDataSetChanged()
            }
            .setNegativeButton("Cancel") { dialog, which ->
                dialog.dismiss()
            }
            .show()
    }

    private fun getEvents() {
        lifecycleScope.launch {
            try {
                val events = withContext(Dispatchers.IO) {
                    eventsDatabase.eventDao().getUserEvent(databaseViewModel.username)
                }

                withContext(Dispatchers.Main) {
                    // 确保 noteList 和 notesAdapter 已经被初始化
                    if (eventsList.isEmpty()) {
                        eventsList.clear()
                        eventsList.addAll(events)
                        eventsAdapter.notifyDataSetChanged()
                    } else {
                        // 插入新数据前，确保 notes 不为空
                        events.takeIf { it.isNotEmpty() }?.let {
                            eventsList.add(0, it[0])
                            eventsAdapter.notifyDataSetChanged()
                        }
                    }
                    eventsRecyclerView.smoothScrollToPosition(0)
                    Log.d("MY_EVENTS", events.toString())
                }
            } catch (e: Exception) { // 捕获并处理异常
                Log.e("MY_NOTES", "Error fetching notes", e)
            }
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    private fun saveEventToDatabase(event: Event) {
        lifecycleScope.launch(Dispatchers.IO) {
            val db = EventsDatabase.getDatabase(requireContext())
            db.eventDao().insertEvent(event)
            eventsList.clear()
            getEvents()
            eventsAdapter.notifyDataSetChanged()
            withContext(Dispatchers.Main) {
                Toast.makeText(requireContext(), "Event saved successfully!", Toast.LENGTH_SHORT).show()
            }
        }
    }
}