package com.example.finalproject.ui.home

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.R
import com.example.finalproject.entities.Note
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

class NotesAdapter(private val notes: List<Note>, private val listener: MyClickListener) :
    RecyclerView.Adapter<NotesAdapter.NoteViewHolder>() {

    lateinit var itemView: View
    interface MyClickListener{
        fun onClickItem(note: Note)
        fun onLongClickItem(note: Note, position: Int)
    }

    inner class NoteViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val titleTextView: TextView = itemView.findViewById(R.id.textViewTitle)
        val dateTextView: TextView = itemView.findViewById(R.id.textViewDate)
        lateinit var currentNote: Note
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): NoteViewHolder {
        itemView = LayoutInflater.from(parent.context)
            .inflate(R.layout.note_item, parent, false)
        val holder = NoteViewHolder(itemView)

        return NoteViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: NoteViewHolder, position: Int) {
        val currentNote = notes[position]
        holder.titleTextView.text = currentNote.title
        holder.dateTextView.text = SimpleDateFormat("yyyy年 MM月 dd日 a HH:mm EEEE", Locale.getDefault()).format(
            Date(currentNote.dateTime)
        )
        holder.currentNote = currentNote

        itemView.setOnClickListener {
            listener.onClickItem(holder.currentNote)
        }

        itemView.setOnLongClickListener {
            listener.onLongClickItem(holder.currentNote, holder.adapterPosition)
            true
        }
    }

    override fun getItemCount(): Int {
        return notes.size
    }
}
