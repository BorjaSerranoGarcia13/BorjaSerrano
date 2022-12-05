using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalCoin : MonoBehaviour
{
    // SPEED ROTATION
   private float tmp_speedRotation;

    [SerializeField]
    float speedRotation = 3.0f,
          waitTime = 0.3f;

    // UP MOVEMENT
    [SerializeField]
    float speed_up = 20.0f;

    private Vector3 up_mov = new Vector3(0.0f, 0.0f, 0.0f);

    private short direction = 1;


    // Start is called before the first frame update
    void Start()
    {
        tmp_speedRotation = speedRotation;
    }

    void Update()
    {
        // ROTATION MANAGEMENT
        if (transform.rotation.y >= 1.0f)
        {
            StartCoroutine(WaitForMove(waitTime));
            transform.Rotate(transform.rotation.x, (-180.0f), transform.rotation.z);
        }

        transform.Rotate(0.0f, speedRotation, 0.0f, Space.World);

        // UP MOVEMENT MANAGEMENT
        up_mov.y = speed_up;
        GetComponent<Rigidbody>().velocity = direction * up_mov * Time.deltaTime;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            Destroy(gameObject);
        }

        if (other.gameObject.CompareTag("LimitEnemy"))
        {
            direction *= (-1);
        }
    }

    IEnumerator WaitForMove(float time)
    {
        speedRotation = 0.0f;
        yield return new WaitForSeconds(time);
        speedRotation = tmp_speedRotation;
    }
}
