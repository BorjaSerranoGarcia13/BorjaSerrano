using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SantaController : MonoBehaviour {

    public float timeAlive = 100.0f;
    public float nextSpawn;

    private Vector3 initPosition;
    public AudioSource audio;
    private float movingTime;
    private bool moving;

    // Start is called before the first frame update
    void Start() {
        initPosition = gameObject.transform.position;
        nextSpawn = Random.Range(Time.time + timeAlive * 1.0f, Time.time + timeAlive * 2.0f);
        audio.Stop();
        moving = false;
        movingTime = 0.0f;
    }

    // Update is called once per frame
    void Update() {
        if (moving) {
            movingTime += Time.deltaTime;
            gameObject.transform.Translate(new Vector3(1.0f, 0.2f, 0.0f));
            if (movingTime >= timeAlive) {
                moving = false;
                nextSpawn = Random.Range(Time.time + timeAlive * 1.0f, Time.time + timeAlive * 2.0f);
                audio.Stop();
                gameObject.transform.position = initPosition;
                movingTime = 0.0f;
            }
        } else if (Time.time >= nextSpawn) {
            audio.Play();
            moving = true;
        }

    }
}
