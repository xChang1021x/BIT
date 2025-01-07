package com.example.finalproject.ui

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import com.example.finalproject.database.EventsDatabase
import com.example.finalproject.database.NotesDatabase
import com.example.finalproject.database.UserDatabase

class DatabaseViewModel(application: Application) : AndroidViewModel(application) {
    val eventsDatabase: EventsDatabase = EventsDatabase.getDatabase(application)
    val notesDatabase: NotesDatabase = NotesDatabase.getDatabase(application)
    val userDatabaase: UserDatabase = UserDatabase.getDatabase(application)
    var username: String = ""
}