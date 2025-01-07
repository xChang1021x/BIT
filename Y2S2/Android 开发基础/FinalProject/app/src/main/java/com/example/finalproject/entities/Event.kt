package com.example.finalproject.entities

import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.ColumnInfo
import java.io.Serializable
import java.util.Date

@Entity(tableName = "events")
data class Event(
    @PrimaryKey(autoGenerate = true) var id: Int = 0,
    @ColumnInfo(name = "title") var title: String = "",
    @ColumnInfo(name = "date_time") var dateTime: Long = 0,
    @ColumnInfo(name = "color") var color: String = "",
    @ColumnInfo(name = "status") var status: Boolean = false,
    @ColumnInfo(name = "user") var user: String = ""
) : Serializable {

}