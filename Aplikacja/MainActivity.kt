import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.testowe.R

class MainActivity : AppCompatActivity() {
    private lateinit var nameEditText: EditText

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        nameEditText = findViewById(R.id.editTextUsername)
        val button1: Button = findViewById(R.id.button1)
        val button2: Button = findViewById(R.id.button2)
        val button3: Button = findViewById(R.id.button3)

        button1.setOnClickListener {
            val name = nameEditText.text.toString()
            showToast("Witaj, $name! Wybrano przycisk 1.")
        }

        button2.setOnClickListener {
            val name = nameEditText.text.toString()
            showToast("Witaj, $name! Wybrano przycisk 2.")
        }

        button3.setOnClickListener {
            val name = nameEditText.text.toString()
            showToast("Witaj, $name! Wybrano przycisk 3.")
        }
    }

    private fun showToast(message: String) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show()
    }
}
