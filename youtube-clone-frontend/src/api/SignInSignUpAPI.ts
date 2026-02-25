import { fetchOptionsGET, fetchOptionsPOST, fetchOptionsPUT } from "../components/fetchOptions";

export type SignInSignUpInfoType = {
    username: string;
    password: string;
    createUser: boolean;
};

export type UserInfoType = {
    userID: number;
    username: string;
}

export function sendSignInSignUpInfo(): UserInfoType {
    const userCredentials: SignInSignUpInfoType = {
        username: "name",
        password: "password",
        createUser: false,
    };

    let retrievedUserData: UserInfoType  = {
        userID: -1,
        username: "",
    };
    
    fetch("http://localhost:3490/signin", {...fetchOptionsPOST,
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(userCredentials),
    })
    .then(response => response.json())
    .then((data) => {
        retrievedUserData = (data as UserInfoType);
    })
    .catch((error) => {
        console.error(error);
    });

    return retrievedUserData;
}
