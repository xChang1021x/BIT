package com.example.finalproject.entities

import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.ColumnInfo
import java.io.Serializable

@Entity(tableName = "notes")
data class Note(
    @PrimaryKey(autoGenerate = true) var id: Int = 0,
    @ColumnInfo(name = "title") var title: String = "",
    @ColumnInfo(name = "date_time") var dateTime: Long = 0,
    @ColumnInfo(name = "note_text") var noteText: String = "",
    @ColumnInfo(name = "image_path") var imagePath: String = "",
    @ColumnInfo(name = "user") var user: String = ""
) : Serializable {

}