package com.example.finalproject.ui.editnote

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
import android.widget.TextView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.core.net.toUri
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.lifecycleScope
import androidx.navigation.fragment.findNavController
import com.example.finalproject.R
import com.example.finalproject.database.NotesDatabase
import com.example.finalproject.databinding.FragmentNoteEditBinding
import com.example.finalproject.entities.Note
import com.example.finalproject.ui.DatabaseViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale
import java.util.regex.Pattern

class EditNoteFragment : Fragment() {

    private var EDIT_NOTE = 0
    private val REQUEST_CODE_PICK_IMAGE = 1
    private val REQUEST_CODE_READ_STORAGE = 2

    private var _binding: FragmentNoteEditBinding? = null
    private val databaseViewModel: DatabaseViewModel by activityViewModels()
    private val binding get() = _binding!!
    private lateinit var inputNoteTitle: EditText
    private lateinit var inputNoteText: EditText
    private lateinit var textDateTime: TextView
    private lateinit var save: Button
    private lateinit var  note: Note
    private var imageUriNote: String = ""
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        arguments?.let {
            note = it.getSerializable("note") as Note
            EDIT_NOTE = 1
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentNoteEditBinding.inflate(inflater, container, false)
        val sharedPreferences = activity?.getSharedPreferences("MyAppPreferences", Context.MODE_PRIVATE)
        val backgroundUri = sharedPreferences?.getString("background", "")
        if (backgroundUri != "") {
            val layoutLinear = binding.editDoneBar
            layoutLinear.background = null
        }
        if (EDIT_NOTE == 1){
            binding.noteTitle.setText(note.title)
            binding.noteContent.setText(note.noteText)
            if (note.imagePath != "") {
                val bitmap = MediaStore.Images.Media.getBitmap(requireContext().contentResolver, note.imagePath.toUri())
                val drawable = BitmapDrawable(resources, bitmap)
                binding.rootLayoutEdit.background = drawable
            }
            imageUriNote = note.imagePath
        }
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        inputNoteTitle = binding.noteTitle // 更新为使用 binding
        inputNoteText = binding.noteContent
        textDateTime = binding.noteDate

        textDateTime.text = SimpleDateFormat("yyyy年 MM月 dd日 a HH:mm EEEE", Locale.getDefault()).format(Date())

        binding.editDone.setOnClickListener {
            saveNote()
        }

        binding.bgImage.setOnClickListener {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
                if (ContextCompat.checkSelfPermission(requireContext(), android.Manifest.permission.READ_MEDIA_IMAGES)
                    != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(requireActivity(), arrayOf(android.Manifest.permission.READ_MEDIA_IMAGES), REQUEST_CODE_READ_STORAGE)
                } else {
                    pickImageFromGallery()
                }
            } else {
                if (ContextCompat.checkSelfPermission(requireContext(), android.Manifest.permission.READ_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(requireActivity(), arrayOf(android.Manifest.permission.READ_EXTERNAL_STORAGE), REQUEST_CODE_READ_STORAGE)
                } else {
                    pickImageFromGallery()
                }
            }
        }

        binding.undo.setOnClickListener {
            undoBackground()
        }

        binding.clearNote.setOnClickListener {
            inputNoteText.setText("")
        }

        binding.shareNote.setOnClickListener {
            showShareDialog()
        }

        binding.editReturn.setOnClickListener {
            findNavController().popBackStack()
        }

    }

    private fun undoBackground() {
        val sharedPreferences = activity?.getSharedPreferences("MyAppPreferences", Context.MODE_PRIVATE)
        val backgroundUri = sharedPreferences?.getString("background", "")

        if (backgroundUri != "") {
            val bitmap = MediaStore.Images.Media.getBitmap(requireContext().contentResolver, backgroundUri?.toUri())
            val drawable = BitmapDrawable(resources, bitmap)
            binding.rootLayoutEdit.background = drawable
            binding.editDoneBar.background = null
        }
        else {
            binding.rootLayoutEdit.setBackgroundResource(R.drawable.gradient_background)
        }
    }

    private fun showShareDialog() {
        val dialogView = LayoutInflater.from(requireContext()).inflate(R.layout.dialog_share_note, null)
        val usernameEditText = dialogView.findViewById<EditText>(R.id.usernameShare)
        val shareButton = dialogView.findViewById<Button>(R.id.share_button)
        val cancelShareButton = dialogView.findViewById<Button>(R.id.cancel_share_button)

        val dialog = AlertDialog.Builder(requireContext())
            .setView(dialogView)
            .create()

        shareButton.setOnClickListener {
            val username = usernameEditText.text.toString()
            lifecycleScope.launch {
                val users = databaseViewModel.userDatabaase.userDao().getUserByUsername(username)
                if (users != null) {
                    val pattern = Pattern.compile("""(\d{4})年 (\d{2})月 (\d{2})日 (AM|PM|上午|下午) (\d{2}):(\d{2}) (.+)""")
                    val matcher = pattern.matcher(textDateTime.text)
                    var dateTimeLong: Date = Date()

                    if (matcher.find()) {
                        val year = matcher.group(1)
                        val month = matcher.group(2)
                        val day = matcher.group(3)
                        val ampm = matcher.group(4)
                        val hour = matcher.group(5)
                        val min = matcher.group(6)
                        if (year != null && month != null && day != null && hour != null && min != null) {
                            dateTimeLong = Date(year.toInt() - 1900, month.toInt() - 1, day.toInt(), hour.toInt(), min.toInt())
                        }
                    }
                    note = Note().apply {
                        title = inputNoteTitle.text.toString()
                        noteText = inputNoteText.text.toString()
                        dateTime = dateTimeLong.time
                        imagePath = imageUriNote
                        user = username
                    }
                    databaseViewModel.notesDatabase.noteDao().insertNote(note)
                    Toast.makeText(requireContext(), "分享成功！！", Toast.LENGTH_SHORT).show()
                    dialog.dismiss()
                }
                else {
                    Toast.makeText(requireContext(), "用户名不存在！", Toast.LENGTH_SHORT).show()
                }
            }
        }

        cancelShareButton.setOnClickListener {
            dialog.dismiss()
        }

        dialog.show()
    }

    private fun saveNote() {
        if (inputNoteTitle.text.trim().isEmpty()) {
            Toast.makeText(requireContext(), "Note title can't be empty!", Toast.LENGTH_SHORT).show()
            return
        } else if (inputNoteText.text.trim().isEmpty()) {
            Toast.makeText(requireContext(), "Note can't be empty!", Toast.LENGTH_SHORT).show()
            return
        }

        val pattern = Pattern.compile("""(\d{4})年 (\d{2})月 (\d{2})日 (AM|PM|上午|下午) (\d{2}):(\d{2}) (.+)""")
        val matcher = pattern.matcher(textDateTime.text)
        var dateTimeLong: Date = Date()

        if (matcher.find()) {
            val year = matcher.group(1)
            val month = matcher.group(2)
            val day = matcher.group(3)
            val ampm = matcher.group(4)
            val hour = matcher.group(5)
            val min = matcher.group(6)
            if (year != null && month != null && day != null && hour != null && min != null) {
                dateTimeLong = Date(year.toInt() - 1900, month.toInt() - 1, day.toInt(), hour.toInt(), min.toInt())
            }
        }


        if (EDIT_NOTE == 0){
            note = Note().apply {
                title = inputNoteTitle.text.toString()
                noteText = inputNoteText.text.toString()
                dateTime = dateTimeLong.time
                imagePath = imageUriNote
                user = databaseViewModel.username
            }
            saveNoteToDatabase(note)
        }
        else if (EDIT_NOTE == 1){
            note.title = inputNoteTitle.text.toString()
            note.noteText = inputNoteText.text.toString()
            note.dateTime = Date().time
            note.imagePath = imageUriNote
            updateNoteToDatabase(note)
        }
    }

    private fun saveNoteToDatabase(note: Note) {
        lifecycleScope.launch(Dispatchers.IO) {
            val db = NotesDatabase.getDatabase(requireContext())
            db.noteDao().insertNote(note)
            withContext(Dispatchers.Main) {
                Toast.makeText(requireContext(), "Note saved successfully!", Toast.LENGTH_SHORT).show()
                findNavController().popBackStack()
            }
        }
    }

    private fun updateNoteToDatabase(note: Note) {
        lifecycleScope.launch(Dispatchers.IO) {
            val db = NotesDatabase.getDatabase(requireContext())
            db.noteDao().update(note)
            withContext(Dispatchers.Main) {
                Toast.makeText(requireContext(), "Note updated successfully!", Toast.LENGTH_SHORT).show()
                findNavController().popBackStack()
            }
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    private fun pickImageFromGallery() {
        val intent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI)
        startActivityForResult(intent, REQUEST_CODE_PICK_IMAGE)
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
                    pickImageFromGallery()
                } else {
                    // Permission denied
                    Toast.makeText(requireContext(), "Permission denied", Toast.LENGTH_SHORT).show()
                }
            }
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == REQUEST_CODE_PICK_IMAGE && resultCode == Activity.RESULT_OK) {
            data?.data?.let { uri ->
                setBackground(uri)
            }
        }
    }

    private fun setBackground(imageUri: Uri) {
        val bitmap = MediaStore.Images.Media.getBitmap(requireContext().contentResolver, imageUri)
        val drawable = BitmapDrawable(resources, bitmap)
        binding.rootLayoutEdit.background = drawable
        imageUriNote = imageUri.toString()
    }
}