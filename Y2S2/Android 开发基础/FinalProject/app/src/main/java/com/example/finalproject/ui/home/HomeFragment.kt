package com.example.finalproject.ui.home

import android.annotation.SuppressLint
import android.app.AlertDialog
import android.content.Context
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import android.util.Log
import android.view.LayoutInflater
import android.view.MenuItem
import android.view.View
import android.view.ViewGroup
import android.widget.PopupMenu
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.lifecycleScope
import androidx.navigation.fragment.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.R
import com.example.finalproject.database.NotesDatabase
import com.example.finalproject.databinding.FragmentHomeBinding
import com.example.finalproject.entities.Note
import com.example.finalproject.ui.DatabaseViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class HomeFragment : Fragment(), NotesAdapter.MyClickListener {

    private var _binding: FragmentHomeBinding? = null
    private lateinit var notesDatabase: NotesDatabase
    private lateinit var notesRecyclerView: RecyclerView
    private lateinit var notesAdapter: NotesAdapter
    private lateinit var noteList: MutableList<Note>
    private val databaseViewModel: DatabaseViewModel by activityViewModels()
    private val binding get() = _binding!!

    override fun onClickItem(note: Note) {
        val bundle = Bundle().apply {
            putSerializable("note", note)
        }
        findNavController().navigate(R.id.navigation_editNote, bundle)
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onLongClickItem(note: Note, position: Int) {
        AlertDialog.Builder(requireContext())
            .setMessage("你要删除这个笔记吗？")
            .setPositiveButton("OK"){ _, which ->
                deleteNotes(note)
            }
            .setNegativeButton("cancel"){ _, which ->
            }
            .create()
            .show()
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        _binding = FragmentHomeBinding.inflate(inflater, container, false)  // 初始化绑定对象

        val sharedPreferences = activity?.getSharedPreferences("MyAppPreferences", Context.MODE_PRIVATE)

        databaseViewModel.username = sharedPreferences?.getString("USER_ID", "").toString()
        notesDatabase = databaseViewModel.notesDatabase

        val backgroundUri = sharedPreferences?.getString("background", "")

        if (backgroundUri != "") {
            binding.toolBar.background = null
        }

        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        notesRecyclerView = binding.recyclerViewNotes.findViewById(R.id.recyclerView_notes)
        val linearLayoutManager = LinearLayoutManager(requireContext())
        notesRecyclerView.layoutManager = linearLayoutManager

        noteList = ArrayList<Note>()

        getNotes()

        notesAdapter = NotesAdapter(noteList, this)
        notesRecyclerView.adapter = notesAdapter

        binding.addNote.setOnClickListener {
            findNavController().navigate(R.id.navigation_editNote)
            noteList.clear()
            getNotes()
        }

        binding.moreSetting.setOnClickListener {
            showPopupMenu(it)
        }

        binding.noteSearch.addTextChangedListener (object: TextWatcher{
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
                //...
            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                //...
            }

            @SuppressLint("NotifyDataSetChanged")
            override fun afterTextChanged(s: Editable?) {
                if (!s.isNullOrEmpty()){
                    noteList.clear()
                    getNotesByKeyword(s.toString())
                    notesAdapter.notifyDataSetChanged()
                }
                else{
                    noteList.clear()
                    getNotes()
                    notesAdapter.notifyDataSetChanged()
                }
            }
        })
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
                        .setMessage("你确定要清除所有笔记吗？")
                        .setPositiveButton("OK") { _, _ ->
                            lifecycleScope.launch {
                                databaseViewModel.notesDatabase.noteDao().clearUserNote(databaseViewModel.username)
                                noteList.clear()
                                notesAdapter.notifyDataSetChanged()
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

    private fun deleteNotes(note: Note) {
        lifecycleScope.launch {
            withContext(Dispatchers.IO) {
                notesDatabase.noteDao().deleteNote(note)
            }
            withContext(Dispatchers.Main) {
                val position = noteList.indexOf(note)
                if (position != -1) {
                    noteList.removeAt(position)
                    notesAdapter.notifyItemRemoved(position)
                }
            }
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    private fun getNotes() {
        lifecycleScope.launch {
            try {
                val notes = withContext(Dispatchers.IO) {
                    notesDatabase.noteDao().getUserNote(databaseViewModel.username)
                }

                withContext(Dispatchers.Main) {
                    noteList.clear()
                    noteList.addAll(notes)
                    notesAdapter.notifyDataSetChanged()
                    notesRecyclerView.smoothScrollToPosition(0)
                    Log.d("MY_NOTES", notes.toString())
                }
            } catch (e: Exception) {
                Log.e("MY_NOTES", "Error fetching notes", e)
            }
        }
    }

    @SuppressLint("NotifyDataSetChanged")
    private fun getNotesByKeyword(keyword: String) {
        lifecycleScope.launch {
            try {
                val notes = withContext(Dispatchers.IO) {
                    notesDatabase.noteDao().searchNotesByTitle(databaseViewModel.username, keyword)
                }
                withContext(Dispatchers.Main) {
                    noteList.clear()
                    noteList.addAll(notes)
                    notesAdapter.notifyDataSetChanged()
                    notesRecyclerView.smoothScrollToPosition(0)
                    Log.d("MY_NOTES", notes.toString())
                }
            } catch (e: Exception) {
                Log.e("MY_NOTES", "Error fetching notes", e)
            }
        }
    }
}


