export type UserData = {
    userStatus: number;
    userID: number;
    username: string;
    userLoggedIn: boolean;
};

export type JWTToken = {
    token: string;
}

export type VideoType = {
    name: string;
    channelName: string;
    views: number;
    length: number;
    videoThumbnail: string;
};

export enum PageOptions {
    SignInSignUp,
    Home,
    Subscription,
    History,
    Playlists,
    MyVideos,
};


