package com.example.finalproject

import android.graphics.drawable.BitmapDrawable
import android.os.Bundle
import android.provider.MediaStore
import android.view.View
import android.widget.LinearLayout
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.core.net.toUri
import androidx.navigation.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.setupActionBarWithNavController
import androidx.navigation.ui.setupWithNavController
import com.example.finalproject.databinding.ActivityMainBinding
import com.example.finalproject.ui.DatabaseViewModel
import com.google.android.material.bottomnavigation.BottomNavigationView

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val databaseViewModel: DatabaseViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val sharedPreferences = getSharedPreferences("MyAppPreferences", MODE_PRIVATE)
        val isLoggedIn = sharedPreferences.getBoolean("IS_LOGGED_IN", false)
        val backgroundUri = sharedPreferences.getString("background", "")

        if (backgroundUri != "") {
            val layoutLinear = findViewById<LinearLayout>(R.id.toolBar)
            val bitmap = MediaStore.Images.Media.getBitmap(this.contentResolver, backgroundUri?.toUri())
            val drawable = BitmapDrawable(resources, bitmap)
            binding.rootLayout.background = drawable
            layoutLinear.background = null
        }
        if (isLoggedIn) {
            databaseViewModel.username = sharedPreferences.getString("USER_ID", "").toString()
        }

        val navView: BottomNavigationView = binding.navView

        val navController = findNavController(R.id.nav_host_fragment_activity_main)
        val appBarConfiguration = AppBarConfiguration(
            setOf(
                R.id.navigation_home, R.id.navigation_dashboard,
                R.id.navigation_notifications, R.id.navigation_profile,
                R.id.navigation_editNote
            )
        )
        setupActionBarWithNavController(navController, appBarConfiguration)
        navView.setupWithNavController(navController)

        navController.addOnDestinationChangedListener { _, destination, _ ->
            if (destination.id == R.id.navigation_editNote) {
                navView.visibility = View.GONE
            } else {
                navView.visibility = View.VISIBLE
            }
        }
    }
}