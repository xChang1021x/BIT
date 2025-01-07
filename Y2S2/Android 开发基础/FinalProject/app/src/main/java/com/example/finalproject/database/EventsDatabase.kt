package com.example.finalproject.database

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase
import com.example.finalproject.dao.EventDao
import com.example.finalproject.entities.Event

@Database(entities = [Event::class], version = 3, exportSchema = true)
abstract class EventsDatabase : RoomDatabase() {
    abstract fun eventDao(): EventDao

    companion object {
        private const val DATABASE_NAME = "events_db"
        private var eventsDatabase: EventsDatabase? = null

        @Synchronized
        fun getDatabase(context: Context): EventsDatabase {
            if (eventsDatabase == null) {
                eventsDatabase = Room.databaseBuilder(
                    context.applicationContext,
                    EventsDatabase::class.java,
                    DATABASE_NAME
                ).build()
            }
            return eventsDatabase!!
        }
    }
}