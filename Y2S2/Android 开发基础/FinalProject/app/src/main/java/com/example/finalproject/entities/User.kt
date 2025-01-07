package com.example.finalproject.entities

import androidx.room.Entity
import androidx.room.PrimaryKey
import androidx.room.ColumnInfo
import java.io.Serializable

@Entity(tableName = "users")
data class User(
    @PrimaryKey var username: String = "",
    @ColumnInfo(name = "password") var password: String = "",
    @ColumnInfo(name = "image") var image: String = ""
) : Serializable {

}