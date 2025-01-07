package com.example.finalproject.ui.profile

import android.annotation.SuppressLint
import android.app.Activity
import android.app.AlertDialog
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.drawable.BitmapDrawable
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.provider.MediaStore
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.core.net.toUri
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.RecyclerView
import com.example.finalproject.MainActivity
import com.example.finalproject.R
import com.example.finalproject.entities.User
import com.example.finalproject.ui.DatabaseViewModel
import com.example.finalproject.ui.notifications.NotificationsAdapter
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.lang.reflect.Array

class ProfileFragment : Fragment() {
        private val REQUEST_CODE_PICK_IMAGE_FOR_BACKGROUND = 1
        private val REQUEST_CODE_READ_STORAGE = 2
        private val REQUEST_CODE_PICK_IMAGE_FOR_PORTRAIT = 3
        private val REQUEST_CODE_READ_STORAGE_PORTRAIT = 4
        private val databaseViewModel: DatabaseViewModel by activityViewModels()
        private var loggedIn: Boolean = false

        private fun refreshFragment() {
                val fragmentTransaction = parentFragmentManager.beginTransaction()
                fragmentTransaction.detach(this).attach(this).commit()
        }

        @SuppressLint("SetTextI18n")
        override fun onCreateView(
                inflater: LayoutInflater, container: ViewGroup?,
                savedInstanceState: Bundle?
        ): View? {
                val view = inflater.inflate(R.layout.fragment_profile, container, false)
                val cntEvents = view.findViewById<TextView>(R.id.cntEvents)
                val cntNotes = view.findViewById<TextView>(R.id.cntNotes)
                val portrait = view.findViewById<ImageView>(R.id.portrait)
                val setBackground = view.findViewById<Button>(R.id.setBackground)
                val clearData = view.findViewById<Button>(R.id.clearData)
                val login = view.findViewById<Button>(R.id.Login)
                val logout = view.findViewById<Button>(R.id.logout)
                val exit = view.findViewById<Button>(R.id.exit)
                val sharedPreferences = activity?.getSharedPreferences("MyAppPreferences", Context.MODE_PRIVATE)

                if (databaseViewModel.username != "") {
                        loggedIn = true
                        login.text = databaseViewModel.username
                        lifecycleScope.launch {
                                if (databaseViewModel.userDatabaase.userDao().getUserByUsername(databaseViewModel.username)?.image != "") {
                                        databaseViewModel.userDatabaase.userDao().getUserByUsername(databaseViewModel.username)?.image?.let {
                                                setPortrait(
                                                        it.toUri())
                                        }
                                }
                        }
                }

                if (loggedIn) {
                        sharedPreferences?.edit()?.apply {
                                putString("USER_ID", databaseViewModel.username)
                                putBoolean("IS_LOGGED_IN", true)
                                apply()
                        }
                }
                else {
                        sharedPreferences?.edit()?.apply {
                                putString("USER_ID", "")
                                putBoolean("IS_LOGGED_IN", false)
                                apply()
                        }
                }

                portrait.setOnClickListener {
                        if (!loggedIn) {
                                showLoginDialog()
                                if (loggedIn) {
                                        login.setText(databaseViewModel.username)
                                        refreshFragment()
                                }
                        }
                        else {
                                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
                                        if (ContextCompat.checkSelfPermission(requireContext(), android.Manifest.permission.READ_MEDIA_IMAGES)
                                                != PackageManager.PERMISSION_GRANTED) {
                                                ActivityCompat.requestPermissions(requireActivity(), arrayOf(android.Manifest.permission.READ_MEDIA_IMAGES), REQUEST_CODE_READ_STORAGE)
                                        } else {
                                                pickImageFromGallery(REQUEST_CODE_PICK_IMAGE_FOR_PORTRAIT)
                                        }
                                } else {
                                        if (ContextCompat.checkSelfPermission(requireContext(), android.Manifest.permission.READ_EXTERNAL_STORAGE)
                                                != PackageManager.PERMISSION_GRANTED) {
                                                ActivityCompat.requestPermissions(requireActivity(), arrayOf(android.Manifest.permission.READ_EXTERNAL_STORAGE), REQUEST_CODE_READ_STORAGE)
                                        } else {
                                                pickImageFromGallery(REQUEST_CODE_PICK_IMAGE_FOR_PORTRAIT)
                                        }
                                }
                        }
                }

                login.setOnClickListener {
                        if (!loggedIn) {
                                showLoginDialog()
                                if (loggedIn) {
                                        login.setText(databaseViewModel.username)
                                        refreshFragment()
                                }
                        }
                }

                logout.setOnClickListener {
                        if (loggedIn) {
                                AlertDialog.Builder(requireContext())
                                        .setMessage("你确定登出账户吗？")
                                        .setPositiveButton("确认"){ _, which ->
                                                loggedIn = false
                                                login.text = "Login"
                                                databaseViewModel.username = ""
                                                portrait.setBackgroundResource(R.drawable.ic_profile_24)
                                                sharedPreferences?.edit()?.apply {
                                                        putString("USER_ID", "")
                                                        putBoolean("IS_LOGGED_IN", false)
                                                        apply()
                                                }
                                                lifecycleScope.launch {
                                                        cntEvents.text = "${databaseViewModel.eventsDatabase.eventDao().getUserEvent(databaseViewModel.username).size}"
                                                        cntNotes.text = "${databaseViewModel.notesDatabase.noteDao().getUserNote(databaseViewModel.username).size}"
                                                }
                                                refreshFragment()
                                        }
                                        .setNegativeButton("取消"){ _, which ->
                                        }
                                        .create()
                                        .show()
                        }
                        else {
                                Toast.makeText(requireContext(), "请先登入账号！", Toast.LENGTH_SHORT).show()
                        }
                }

                setBackground.setOnClickListener {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
                                if (ContextCompat.checkSelfPermission(requireContext(), android.Manifest.permission.READ_MEDIA_IMAGES)
                                        != PackageManager.PERMISSION_GRANTED) {
                                        ActivityCompat.requestPermissions(requireActivity(), arrayOf(android.Manifest.permission.READ_MEDIA_IMAGES), REQUEST_CODE_READ_STORAGE)
                                } else {
                                        pickImageFromGallery(REQUEST_CODE_PICK_IMAGE_FOR_BACKGROUND)
                                }
                        } else {
                                if (ContextCompat.checkSelfPermission(requireContext(), android.Manifest.permission.READ_EXTERNAL_STORAGE)
                                        != PackageManager.PERMISSION_GRANTED) {
                                        ActivityCompat.requestPermissions(requireActivity(), arrayOf(android.Manifest.permission.READ_EXTERNAL_STORAGE), REQUEST_CODE_READ_STORAGE)
                                } else {
                                        pickImageFromGallery(REQUEST_CODE_PICK_IMAGE_FOR_BACKGROUND)
                                }
                        }
                }

                clearData.setOnClickListener {
                        AlertDialog.Builder(requireContext())
                                .setMessage("你确定要清除所有数据吗？")
                                .setPositiveButton("OK") { _, _ ->
                                        lifecycleScope.launch {
                                                databaseViewModel.eventsDatabase.eventDao().clearUserEvents(databaseViewModel.username)
                                                databaseViewModel.notesDatabase.noteDao().clearUserNote(databaseViewModel.username)
                                        }
                                }
                                .setNegativeButton("cancel") { _, _ -> }
                                .create()
                                .show()
                }

                exit.setOnClickListener {

                        requireActivity().finishAffinity()

                }

                lifecycleScope.launch {
                        cntEvents.text = "${databaseViewModel.eventsDatabase.eventDao().getUserEvent(databaseViewModel.username).size}"
                        cntNotes.text = "${databaseViewModel.notesDatabase.noteDao().getUserNote(databaseViewModel.username).size}"
                }

                return view
        }

        private fun showLoginDialog() {
                val dialogView = LayoutInflater.from(requireContext()).inflate(R.layout.dialog_login, null)
                val usernameEditText = dialogView.findViewById<EditText>(R.id.username)
                val passwordEditText = dialogView.findViewById<EditText>(R.id.password)
                val loginButton = dialogView.findViewById<Button>(R.id.login_button)
                val registerButton = dialogView.findViewById<Button>(R.id.register_button)
                val cancelLoginButton = dialogView.findViewById<Button>(R.id.cancel_login_button)

                val dialog = AlertDialog.Builder(requireContext())
                        .setView(dialogView)
                        .create()

                loginButton.setOnClickListener {
                        val username = usernameEditText.text.toString()
                        val password = passwordEditText.text.toString()
                        // Perform login logic here (e.g., authenticate with server)
                        lifecycleScope.launch {
                                val user = databaseViewModel.userDatabaase.userDao().getUserByUsername(username)
                                if (user != null && password == user.password) {
                                        loggedIn = true
                                        databaseViewModel.username = username
                                        Toast.makeText(requireContext(), "登入成功", Toast.LENGTH_SHORT).show()
                                        val login = view?.findViewById<Button>(R.id.Login)
                                        val cntEvent = view?.findViewById<TextView>(R.id.cntEvents)
                                        val cntNotes = view?.findViewById<TextView>(R.id.cntNotes)
                                        cntEvent?.text = "${databaseViewModel.eventsDatabase.eventDao().getUserEvent(databaseViewModel.username).size}"
                                        cntNotes?.text = "${databaseViewModel.notesDatabase.noteDao().getUserNote(databaseViewModel.username).size}"
                                        login?.text = username
                                        val sharedPreferences = activity?.getSharedPreferences("MyAppPreferences", Context.MODE_PRIVATE)
                                        sharedPreferences?.edit()?.apply {
                                                putString("USER_ID", databaseViewModel.username)
                                                putBoolean("IS_LOGGED_IN", true)
                                                apply()
                                        }
                                        if (user.image != "") {
                                                setPortrait(user.image.toUri())
                                        }
                                        refreshFragment()
                                        dialog.dismiss()
                                }
                                else {
                                        Toast.makeText(requireContext(), "用户名或密码不正确", Toast.LENGTH_SHORT).show()
                                }
                        }
                }

                registerButton.setOnClickListener {
                        dialog.dismiss()
                        showRegisterDialog()
                }

                cancelLoginButton.setOnClickListener {
                        dialog.dismiss()
                }

                dialog.show()
        }

        private fun showRegisterDialog() {
                val dialogView = LayoutInflater.from(requireContext()).inflate(R.layout.dialog_register, null)
                val registerUsernameEditText = dialogView.findViewById<EditText>(R.id.register_username)
                val registerPasswordEditText = dialogView.findViewById<EditText>(R.id.register_password)
                val registerConfirmPasswordEditText = dialogView.findViewById<EditText>(R.id.register_confirm_password)
                val registerSubmitButton = dialogView.findViewById<Button>(R.id.register_submit_button)
                val cancelRegisterButton = dialogView.findViewById<Button>(R.id.cancel_register_button)

                val dialog = AlertDialog.Builder(requireContext())
                        .setView(dialogView)
                        .create()

                registerSubmitButton.setOnClickListener {
                        val name = registerUsernameEditText.text.toString()
                        val ipassword = registerPasswordEditText.text.toString()
                        val confirmPassword = registerConfirmPasswordEditText.text.toString()
                        if (ipassword != confirmPassword) {
                                Toast.makeText(requireContext(), "密码不一致！", Toast.LENGTH_SHORT).show()
                        }
                        else {
                                lifecycleScope.launch {
                                        var user = databaseViewModel.userDatabaase.userDao().getUserByUsername(name)
                                        if (user == null) {
                                                user = User().apply {
                                                        username = name
                                                        password = ipassword
                                                }
                                                databaseViewModel.userDatabaase.userDao().insert(user)
                                                Toast.makeText(requireContext(), "注册成功！", Toast.LENGTH_SHORT).show()
                                                dialog.dismiss()
                                        }
                                        else {
                                                Toast.makeText(requireContext(), "用户名已存在", Toast.LENGTH_SHORT).show()
                                        }
                                }
                        }
                }

                cancelRegisterButton.setOnClickListener {
                        dialog.dismiss()
                }

                dialog.show()
        }


        private fun pickImageFromGallery(REQUEST_CODE: Int) {
                val intent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI)
                startActivityForResult(intent, REQUEST_CODE)
        }

        override fun onRequestPermissionsResult(
                requestCode: Int,
                permissions: kotlin.Array<out String>,
                grantResults: IntArray
        ) {
                when (requestCode) {
                        REQUEST_CODE_READ_STORAGE -> {
                                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                                        // Permission granted
                                        pickImageFromGallery(REQUEST_CODE_PICK_IMAGE_FOR_BACKGROUND)
                                } else {
                                        // Permission denied
                                        Toast.makeText(requireContext(), "Permission denied", Toast.LENGTH_SHORT).show()
                                }
                        }
                        REQUEST_CODE_READ_STORAGE_PORTRAIT -> {
                                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                                        // Permission granted
                                        pickImageFromGallery(REQUEST_CODE_PICK_IMAGE_FOR_PORTRAIT)
                                } else {
                                        // Permission denied
                                        Toast.makeText(requireContext(), "Permission denied", Toast.LENGTH_SHORT).show()
                                }
                        }
                }
        }

        override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
                super.onActivityResult(requestCode, resultCode, data)
                if (requestCode == REQUEST_CODE_PICK_IMAGE_FOR_BACKGROUND && resultCode == Activity.RESULT_OK) {
                        data?.data?.let { uri ->
                                setBackground(uri)
                        }
                }
                else if (requestCode == REQUEST_CODE_PICK_IMAGE_FOR_PORTRAIT && resultCode == Activity.RESULT_OK) {
                        data?.data?.let { uri ->
                                savePortrait(uri)
                                setPortrait(uri)
                        }
                }
        }

        private fun savePortrait(imageUri: Uri) {
                lifecycleScope.launch {
                        val user = databaseViewModel.userDatabaase.userDao().getUserByUsername(databaseViewModel.username)
                        user?.image = imageUri.toString()
                        if (user != null) {
                                databaseViewModel.userDatabaase.userDao().update(user)
                        }
                }
        }
        private fun setPortrait(imageUri: Uri) {
                val portrait = view?.findViewById<ImageView>(R.id.portrait)
                val bitmap = MediaStore.Images.Media.getBitmap(requireContext().contentResolver, imageUri)
                val drawable = BitmapDrawable(resources, bitmap)
                portrait?.background = drawable
        }

        private fun setBackground(imageUri: Uri) {
                val rootLayout = view?.findViewById<ConstraintLayout>(R.id.rootLayout)
                val bitmap = MediaStore.Images.Media.getBitmap(requireContext().contentResolver, imageUri)
                val drawable = BitmapDrawable(resources, bitmap)
                val sharedPreferences = activity?.getSharedPreferences("MyAppPreferences", Context.MODE_PRIVATE)
                sharedPreferences?.edit()?.apply {
                        putString("background", imageUri.toString())
                        apply()
                }
                val intent = Intent(requireContext(), MainActivity::class.java)
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK)
                rootLayout?.background = drawable
                startActivity(intent)
                requireActivity().finish()
        }
}