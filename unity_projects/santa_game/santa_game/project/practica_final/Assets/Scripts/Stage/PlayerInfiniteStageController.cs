using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInfiniteStageController : MonoBehaviour
{
    public delegate void PlayerDistanceWalked(float distance);
    public event PlayerDistanceWalked OnPlayerDistanceWalked;

    public float updateDistanceEach = 5.0f;

    private float distance;
    private float lastDistance;

    void Start() {
        distance = 0.0f;
        lastDistance = 0.0f;
    }

    void Update() {
        distance = (gameObject.transform.position - new Vector3(gameObject.transform.position.x , gameObject.transform.position.y, 0.0f)).magnitude;

        if (distance >= lastDistance + updateDistanceEach) {
            lastDistance = distance;
            if (OnPlayerDistanceWalked != null) {
                OnPlayerDistanceWalked(distance);
            }
        }
    }

}
