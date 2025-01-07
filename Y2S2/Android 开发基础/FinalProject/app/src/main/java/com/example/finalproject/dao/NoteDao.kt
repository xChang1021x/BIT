package com.example.finalproject.dao

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.finalproject.entities.Note

@Dao
interface NoteDao {
    @Query("SELECT * FROM notes ORDER BY date_time DESC, id DESC")
    suspend fun getAllNotes(): List<Note>

    @Query("SELECT * FROM notes WHERE user = :user AND title LIKE '%' || :keyword || '%' ORDER BY date_time DESC, id DESC")
    suspend fun searchNotesByTitle(user: String, keyword: String): List<Note>

    @Query("SELECT * FROM notes WHERE user = :user ORDER BY date_time DESC, id DESC")
    suspend fun getUserNote(user: String): List<Note>

    @Query("DELETE FROM notes WHERE user = :user")
    suspend fun clearUserNote(user: String)

    @Query("DELETE FROM notes")
    suspend fun clear()

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertNote(note: Note)

    @Delete
    suspend fun deleteNote(note: Note)

    @Update
    suspend fun update(note: Note)
}