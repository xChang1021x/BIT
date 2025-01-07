package com.example.finalproject.dao

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.finalproject.entities.Event

@Dao
interface EventDao {
    @Query("SELECT * FROM events ORDER BY date_time DESC, id DESC")
    suspend fun getAllEvents(): List<Event>

    @Query("SELECT * FROM events WHERE user = :user AND date_time > :stime AND date_time < :etime ORDER BY date_time ASC, id ASC")
    suspend fun getEventByTime(user: String, stime: Long, etime: Long): List<Event>

    @Query("SELECT * FROM events WHERE user = :user ORDER BY date_time DESC, id DESC")
    suspend fun getUserEvent(user: String): List<Event>

    @Query("DELETE FROM events WHERE user = :user")
    suspend fun clearUserEvents(user: String)

    @Query("DELETE FROM events")
    suspend fun clearEvents()

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertEvent(event: Event)

    @Delete
    suspend fun deleteEvent(event: Event)

    @Update
    suspend fun update(event: Event)
}