using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnPoint : MonoBehaviour {

    public delegate void PlayerReachedSpawnPoint(Transform spawnPointTransform);
    public event PlayerReachedSpawnPoint OnPlayerReachedSpawnPoint;

    private void OnTriggerEnter(Collider other) {
        if (other.gameObject.CompareTag("Respawn")) {
            if (OnPlayerReachedSpawnPoint != null) {
                OnPlayerReachedSpawnPoint(other.gameObject.transform);
            }
        }
    }

}
