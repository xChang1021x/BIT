package com.example.finalproject.database

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase
import com.example.finalproject.dao.UserDao
import com.example.finalproject.entities.User

@Database(entities = [User::class], version = 2, exportSchema = true)
abstract class UserDatabase : RoomDatabase() {
    abstract fun userDao(): UserDao

    companion object {
        private const val DATABASE_NAME = "users_db"
        private var userDatabase: UserDatabase? = null

        @Synchronized
        fun getDatabase(context: Context): UserDatabase {
            if (userDatabase == null) {
                userDatabase = Room.databaseBuilder(
                    context.applicationContext,
                    UserDatabase::class.java,
                    DATABASE_NAME
                ).build()
            }
            return userDatabase!!
        }
    }
}