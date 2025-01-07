package com.example.finalproject.database

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase
import com.example.finalproject.dao.NoteDao
import com.example.finalproject.entities.Note

@Database(entities = [Note::class], version = 4, exportSchema = true)
abstract class NotesDatabase : RoomDatabase() {
    abstract fun noteDao(): NoteDao

    companion object {
        private const val DATABASE_NAME = "notes_db"
        private var notesDatabase: NotesDatabase? = null

        @Synchronized
        fun getDatabase(context: Context): NotesDatabase {
            if (notesDatabase == null) {
                notesDatabase = Room.databaseBuilder(
                    context.applicationContext,
                    NotesDatabase::class.java,
                    DATABASE_NAME
                ).build()
            }
            return notesDatabase!!
        }


    }
}