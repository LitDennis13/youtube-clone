import { UserData, JWTToken } from "../types";
import { fetchOptionsGET, fetchOptionsPOST, fetchOptionsPUT } from "../components/fetchOptions";

export type UserCredentials = {
    username: string;
    password: string;
    createUser: boolean;
};

async function fetchUserData(): Promise<void | UserData> {
    let retrievedUserData: UserData = {
        userStatus: 1,
        userID: -1,
        username: "",
        userLoggedIn: false,
    };
    
    return await fetch("http://localhost:3490/user_data/fetch_user_data", {...fetchOptionsGET})
    .then(response => response.json())
    .then((data) => {
        retrievedUserData = (data as UserData);
        return retrievedUserData;
    })
    .catch((error) => {
        console.error(error);
    });
}


async function authenticate(userCredentials: UserCredentials): Promise<void | JWTToken> {
    return await fetch("http://localhost:3490/user_data/authentication", {...fetchOptionsPOST,
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(userCredentials),
    })
    .then(response => response.json())
    .then((data) => {
        return (data as JWTToken);
    })
    .catch((error) => {
        console.error(error);
    });
}

export { fetchUserData, authenticate };